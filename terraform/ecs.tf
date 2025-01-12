resource "aws_iam_role_policy_attachment" "ecs_task_execution_cloudwatch" {
  role       = aws_iam_role.ecs_task_execution_role.name
  policy_arn = "arn:aws:iam::aws:policy/service-role/AmazonECSTaskExecutionRolePolicy"
}

# Create the secret with variables
data "aws_secretsmanager_secret" "mysql_master_config" {
  name = "${local.environment}/mysql/master/config"
}

data "aws_secretsmanager_secret_version" "mysql_master_config" {
  secret_id = data.aws_secretsmanager_secret.mysql_master_config.id
}


# ECS Task Definition using the secret
resource "aws_ecs_task_definition" "so_task" {
  family                   = "${local.environment}-task"
  requires_compatibilities = ["FARGATE"]
  network_mode            = "awsvpc"
  cpu                     = 256
  memory                  = 512
  execution_role_arn      = aws_iam_role.ecs_execution_role.arn
  task_role_arn           = aws_iam_role.ecs_task_role.arn

  container_definitions = jsonencode([
    {
      name  = "so-app" # Updated to match the ECS service
      # image = "${data.aws_ecr_repository.swindev_ecr.repository_url}:latest"
      image = "905418316682.dkr.ecr.us-west-2.amazonaws.com/swinney/so-app:202551062351"
      essential = true

    environment = [
      {
        name  = "DB_USER"
        value = jsondecode(data.aws_secretsmanager_secret_version.mysql_master_config.secret_string)["username"]
      },
      {
        name  = "DB_PASSWD"
        value = jsondecode(data.aws_secretsmanager_secret_version.mysql_master_config.secret_string)["password"]
      },
      {
        name  = "DB_HOST"
        value = jsondecode(data.aws_secretsmanager_secret_version.mysql_master_config.secret_string)["host"]
      },
      {
        name  = "DB_NAME"
        value = jsondecode(data.aws_secretsmanager_secret_version.mysql_master_config.secret_string)["dbname"]
      }
    ]


      portMappings = [  # Ensure port 80 is mapped
        {
          containerPort = 80
          hostPort      = 80
          protocol      = "tcp"
        }
      ]

      entryPoint = [
        "sh",
        "-c",
        <<-EOT
        # Write full JSON
        echo "$DB_SECRET" > /etc/container_environment.json
        


        # Read the secret value and create individual files
        secret_json=$(echo $DB_SECRET | jq -r '.')
        
        # Create directory if it doesn't exist
        mkdir -p /etc/container_environment
        
        # Create individual environment files
        echo $secret_json | jq -r '.username' > /etc/container_environment/DB_USER
        echo $secret_json | jq -r '.password' > /etc/container_environment/DB_PASSWD
        echo $secret_json | jq -r '.host' > /etc/container_environment/DB_HOST
        echo $secret_json | jq -r '.port' > /etc/container_environment/DB_PORT
        echo $secret_json | jq -r '.dbname' > /etc/container_environment/DB_NAME
        
        # Create the JSON dump
        echo $secret_json > /etc/container_environment.json
        
        # Set proper permissions
        chown -R www-data:www-data /etc/container_environment
        chmod 640 /etc/container_environment/*
        chmod 640 /etc/container_environment.json
        
        # Execute my_init
        /usr/bin/supervisord -n -c /etc/supervisor/supervisord.conf
        EOT
      ]

      
      # Single secret containing all values
      secrets = [
        {
          name      = "DB_SECRET"
          valueFrom = data.aws_secretsmanager_secret_version.mysql_master_config.arn
        }
      ]
      
      logConfiguration = {
        logDriver = "awslogs"
        options = {
          awslogs-group         = "/ecs/${local.environment}/so-app"
          awslogs-region        = "us-west-2"
          awslogs-stream-prefix = "ecs"
        }
      }
    }
  ])
}

resource "aws_ecs_service" "swindev_service" {
  name            = format("%s-ecs-service", local.environment)
  cluster         = aws_ecs_cluster.swindev_ecs_cluster.id
  task_definition = aws_ecs_task_definition.so_task.arn
  desired_count   = 1
  launch_type     = "FARGATE"
  enable_execute_command = true

  network_configuration {
    subnets = [
      aws_subnet.swindev_public_subnet_1.id,  # Subnet in AZ1
      aws_subnet.swindev_public_subnet_2.id   # Subnet in AZ2
    ]
    security_groups = [aws_security_group.swindev_ecs_sg.id]
    assign_public_ip = true
  }

  load_balancer {
    target_group_arn = aws_lb_target_group.so_app_target_group.arn
    container_name   = "so-app"
    container_port   = 80
  }

  depends_on = [
    aws_internet_gateway.swindev_ecs_igw,
    aws_lb.so_app_lb
  ]

}

# Attach the custom S3 policy to the ECS task execution role
resource "aws_iam_role_policy_attachment" "ecs_task_s3_policy_attachment" {
  role       = aws_iam_role.ecs_task_execution_role.name
  policy_arn = aws_iam_policy.ecs_task_s3_policy.arn
}

# Create the CloudWatch log groups
resource "aws_cloudwatch_log_group" "app" {
    name              = "/ecs/${local.environment}/so-app"
    retention_in_days = 7
}

# ECS Security Group
resource "aws_security_group" "swindev_ecs_sg" {
  name   = "${local.environment}-ecs-sg"
  vpc_id = aws_vpc.swindev_ecs_vpc.id

  ingress {
    from_port   = 80
    to_port     = 80
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  ingress {
    from_port   = 443
    to_port     = 443
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

# Now create the security group rules separately
resource "aws_security_group_rule" "ecs_to_rds" {
  type                     = "ingress"
  from_port                = 3306
  to_port                  = 3306
  protocol                 = "tcp"
  source_security_group_id = aws_security_group.swindev_ecs_sg.id
  security_group_id        = aws_security_group.rds_sg.id
}


resource "aws_iam_role_policy_attachment" "ecs_task_rds" {
  role       = aws_iam_role.ecs_task_role.name
  policy_arn = "arn:aws:iam::aws:policy/AmazonRDSFullAccess"
}


resource "aws_appautoscaling_target" "ecs_scaling" {
  service_namespace  = "ecs"
  resource_id        = "service/${aws_ecs_cluster.swindev_ecs_cluster.name}/${aws_ecs_service.swindev_service.name}"
  scalable_dimension = "ecs:service:DesiredCount"
  min_capacity       = 1
  max_capacity       = 2
}

resource "aws_appautoscaling_policy" "cpu_scaling" {
  name                   = "cpu-scaling"
  policy_type            = "TargetTrackingScaling"
  resource_id            = aws_appautoscaling_target.ecs_scaling.resource_id
  scalable_dimension     = aws_appautoscaling_target.ecs_scaling.scalable_dimension
  service_namespace      = "ecs"

  target_tracking_scaling_policy_configuration {
    target_value       = 50.0
    predefined_metric_specification {
      predefined_metric_type = "ECSServiceAverageCPUUtilization"
    }
  }
}

resource "aws_iam_role_policy" "so_ecs_secrets_access" {
  name   = "ecs-task-secrets-policy"
  role   = aws_iam_role.ecs_task_execution_role.name
  policy = jsonencode({
    Version = "2012-10-17",
    Statement = [
      {
        Effect   = "Allow",
        Action   = [
          "secretsmanager:GetSecretValue"
        ],
        Resource = [
          "arn:aws:secretsmanager:us-west-2:905418316682:secret:dev/mysql/user/swindev/password-WXqJIb"
        ]
      }
    ]
  })
}

resource "aws_iam_role" "ecs_execution_role" {
  name = "ecs-execution-role"

  assume_role_policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Effect = "Allow"
        Principal = {
          Service = "ecs-tasks.amazonaws.com"
        }
        Action = "sts:AssumeRole"
      }
    ]
  })
}

resource "aws_iam_role_policy_attachment" "ecs_task_execution_secrets_manager" {
  role       = aws_iam_role.ecs_execution_role.name
  policy_arn = "arn:aws:iam::aws:policy/SecretsManagerReadWrite"
}

# Task Role Policy for Execute Command
resource "aws_iam_role_policy" "ecs_task_role_policy" {
  name = "ecs-task-role-policy"
  role = aws_iam_role.ecs_task_role.id

  policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Effect = "Allow"
        Action = "*"
        Resource = "*"
      }
    ]
  })
}

resource "aws_iam_role" "ecs_task_role" {
  name = "ecs_task_role"

  assume_role_policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Effect = "Allow"
        Principal = {
          Service = "ecs-tasks.amazonaws.com"
        }
        Action = "sts:AssumeRole"
      }
    ]
  })
}


resource "aws_iam_policy" "ecs_execution_policy" {
  name        = "${local.environment}-ecs-execution-policy"
  description = "Policy to allow ECS to pull images from ECR and log to CloudWatch"

  policy = jsonencode({
    Version = "2012-10-17",
    Statement = [
      {
        Effect = "Allow",
        Action = [
          "ecr:GetAuthorizationToken",
          "ecr:BatchCheckLayerAvailability",
          "ecr:BatchGetImage",
          "ecr:GetDownloadUrlForLayer"
        ],
        Resource = "*"
      },
      {
        Effect = "Allow",
        Action = [
          "logs:CreateLogStream",
          "logs:PutLogEvents"
        ],
        Resource = [
          "arn:aws:logs:*:*:log-group:/ecs/*",
          "arn:aws:logs:*:*:log-group:/ecs/*:log-stream:*"
        ]
      }
    ]
  })
}

resource "aws_iam_role_policy_attachment" "ecs_execution_role_attachment" {
  role       = aws_iam_role.ecs_execution_role.name
  policy_arn = aws_iam_policy.ecs_execution_policy.arn
}
