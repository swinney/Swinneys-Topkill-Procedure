# file_path = "/mnt/data/swindev_ecs_vpc_config.tf"

provider "aws" {
  region = "us-west-2"
}

# Define the environment dynamically based on the current workspace
locals {
  environment = terraform.workspace
}

variable "environments" {
  description = "List of environments to create IAM resources for"
  default     = ["dev", "staging", "prod"]
}

# VPC setup
resource "aws_vpc" "swindev_ecs_vpc" {
  cidr_block = "10.0.0.0/16"  # Ensure this matches your VPC's actual CIDR range
  enable_dns_support   = true
  enable_dns_hostnames = true
  tags = {
    Name = "${local.environment}-ecs-vpc"
  }
}

resource "aws_subnet" "swindev_public_subnet_1" {
  vpc_id                  = aws_vpc.swindev_ecs_vpc.id
  cidr_block              = "10.0.1.0/24"  # Valid CIDR block
  availability_zone       = "us-west-2a"   # First Availability Zone
  map_public_ip_on_launch = true
  tags = {
    Name = "${local.environment}-public-subnet-1"
  }
}

resource "aws_subnet" "swindev_public_subnet_2" {
  vpc_id                  = aws_vpc.swindev_ecs_vpc.id
  cidr_block              = "10.0.2.0/24"  # Valid CIDR block
  availability_zone       = "us-west-2b"   # Second Availability Zone
  map_public_ip_on_launch = true
  tags = {
    Name = "${local.environment}-public-subnet-2"
  }
}


resource "aws_internet_gateway" "swindev_ecs_igw" {
  vpc_id = aws_vpc.swindev_ecs_vpc.id
  tags = {
    Name = "${local.environment}-ecs-igw"
  }
}

resource "aws_route_table" "swindev_public_rt" {
  vpc_id = aws_vpc.swindev_ecs_vpc.id
  tags = {
    Name = "${local.environment}-ecs-public-rt"
  }
}

resource "aws_route" "swindev_public_route" {
  route_table_id         = aws_route_table.swindev_public_rt.id
  destination_cidr_block = "0.0.0.0/0"
  gateway_id             = aws_internet_gateway.swindev_ecs_igw.id
}

resource "aws_route_table_association" "swindev_public_subnet_1_association" {
  subnet_id      = aws_subnet.swindev_public_subnet_1.id
  route_table_id = aws_route_table.swindev_public_rt.id
}

resource "aws_route_table_association" "swindev_public_subnet_2_association" {
  subnet_id      = aws_subnet.swindev_public_subnet_2.id
  route_table_id = aws_route_table.swindev_public_rt.id
}

# ECS Cluster
resource "aws_ecs_cluster" "swindev_ecs_cluster" {
  name = "${local.environment}-ecs-cluster"
}

# IAM Groups, Users, and Policies
resource "aws_iam_group" "terraform_group" {
  count = length(var.environments)

  name = "terraform-${var.environments[count.index]}"
}

resource "aws_iam_group_policy" "terraform_group_policy" {
  count = length(var.environments)

  group = aws_iam_group.terraform_group[count.index].name

  policy = jsonencode({
    Version = "2012-10-17",
    Statement = [
      {
        Effect   = "Allow",
        Action   = [
          "ec2:*",
          "ecs:*",
          "ecr:*",
          "iam:PassRole",
          "s3:*"
        ],
        Resource = [
          "arn:aws:ec2:*:*:vpc/*",
          "arn:aws:ecs:*:*:cluster/${var.environments[count.index]}-*",
          "arn:aws:ecr:*:*:repository/${var.environments[count.index]}-*",
          "arn:aws:iam::*:role/${var.environments[count.index]}-*",
          "arn:aws:s3:::${var.environments[count.index]}-images-bucket",
          "arn:aws:s3:::${var.environments[count.index]}-images-bucket/*"
        ]
      }
    ]
  })
}

resource "aws_iam_user" "terraform_user" {
  count = length(var.environments)

  name = "terraform-${var.environments[count.index]}-user"
}

resource "aws_iam_user_group_membership" "terraform_user_group_membership" {
  count = length(var.environments)

  user   = aws_iam_user.terraform_user[count.index].name
  groups = [aws_iam_group.terraform_group[count.index].name]
}

resource "aws_iam_access_key" "terraform_access_key" {
  count = length(var.environments)

  user = aws_iam_user.terraform_user[count.index].name
}


resource "aws_iam_policy" "ecs_task_s3_policy" {
  name   = "${local.environment}-ecs-task-s3-policy"
  policy = jsonencode({
    Version = "2012-10-17",
    Statement = [
      {
        Effect = "Allow",
        Action = [
          "s3:PutObject",
          "s3:GetObject",
          "s3:DeleteObject",
          "s3:ListBucket"
        ],
        Resource = [
          "arn:aws:s3:::${local.environment}-images-bucket",
          "arn:aws:s3:::${local.environment}-images-bucket/*"
        ]
      }
    ]
  })
}

resource "aws_iam_role" "ecs_task_execution_role" {
  name = "ecs-task-execution-role"
  assume_role_policy = jsonencode({
    Version = "2012-10-17",
    Statement = [
      {
        Action = "sts:AssumeRole",
        Effect = "Allow",
        Principal = {
          Service = "ecs-tasks.amazonaws.com"
        }
      }
    ]
  })
}

# Attach the AWS managed policy for ECS task execution
resource "aws_iam_role_policy_attachment" "ecs_task_execution_role_policy" {
  role       = aws_iam_role.ecs_task_execution_role.name
  policy_arn = "arn:aws:iam::aws:policy/service-role/AmazonECSTaskExecutionRolePolicy"
}

resource "aws_iam_policy" "terraform_policy" {
  name        = "terraform-deployment-policy"
  description = "Policy for Terraform deployments"

  policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Action = "*"
        Effect = "Allow"
        Resource = "*"
      }
    ]
  })
}

# # If you want to attach this policy to an IAM user or role, you can use:
# resource "aws_iam_user_policy_attachment" "terraform_policy_attach" {
#   user       = "TerraformUser"  # Replace with your actual IAM user name
#   policy_arn = aws_iam_policy.terraform_policy.arn
# }

# # Optional: If you want to use this with a role instead of a user
# resource "aws_iam_role" "terraform_role" {
#   name = "TerraformRole"

#   assume_role_policy = jsonencode({
#     Version = "2012-10-17"
#     Statement = [
#       {
#         Action = "sts:AssumeRole"
#         Effect = "Allow"
#         Principal = {
#           Service = "ec2.amazonaws.com"  # Adjust based on your needs
#         }
#       }
#     ]
#   })
# }

# resource "aws_iam_role_policy_attachment" "terraform_policy_role_attach" {
#   role       = aws_iam_role.terraform_role.name
#   policy_arn = aws_iam_policy.terraform_policy.arn
# }

# Add custom policy for SSM session manager
resource "aws_iam_role_policy" "ecs_task_execution_role_policy" {
  name = "ecs-task-execution-role-policy"
  role = aws_iam_role.ecs_task_execution_role.id

  policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Effect = "Allow"
        Action = [
          "ssmmessages:CreateControlChannel",
          "ssmmessages:CreateDataChannel",
          "ssmmessages:OpenControlChannel",
          "ssmmessages:OpenDataChannel",
          "ssm:UpdateInstanceInformation"
        ]
        Resource = "*"
      }
    ]
  })
}