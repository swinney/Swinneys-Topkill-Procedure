# Security Group for Redis
resource "aws_security_group" "redis_sg" {
  name        = "${local.environment}-redis-sg"
  description = "Security group for Redis cluster"
  vpc_id      = aws_vpc.swindev_ecs_vpc.id

  ingress {
    from_port   = 6379
    to_port     = 6379
    protocol    = "tcp"
    security_groups = [aws_security_group.swindev_ecs_sg.id] # Replace with appropriate ECS SG
  }

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    Name = "${local.environment}-redis-sg"
  }
}

# Subnet Group for Redis
resource "aws_elasticache_subnet_group" "redis_subnet_group" {
  name       = "${local.environment}-redis-subnet-group"
  subnet_ids = [aws_subnet.swindev_public_subnet_1.id, aws_subnet.swindev_public_subnet_2.id]

  tags = {
    Name = "${local.environment}-redis-subnet-group"
  }
}

# Parameter group for Redis 7
resource "aws_elasticache_parameter_group" "redis_params" {
  family = "redis7"
  name   = "dev-redis-params"

  parameter {
    name  = "maxmemory-policy"
    value = "allkeys-lru"
  }
}

# Redis Cluster
resource "aws_elasticache_cluster" "redis_cluster" {
  cluster_id           = "${local.environment}-redis-cluster"
  engine               = "redis"
  engine_version      = "7.0"  # Using Redis 7
  node_type            = "cache.t3.micro" # Adjust size as needed
  num_cache_nodes      = 1
  parameter_group_name = aws_elasticache_parameter_group.redis_params.name
  port                 = 6379
  subnet_group_name    = aws_elasticache_subnet_group.redis_subnet_group.name
  security_group_ids   = [aws_security_group.redis_sg.id]
  
  # Recommended settings for dev
  auto_minor_version_upgrade = true
  maintenance_window        = "sun:05:00-sun:06:00"
  snapshot_window          = "03:00-04:00"
  snapshot_retention_limit = 7

  tags = {
    Name = "${local.environment}-redis-cluster"
  }
}

resource "aws_iam_policy" "redis_access_policy" {
  name        = "${local.environment}-redis-access"
  description = "Policy to allow ECS tasks to access Redis"
  policy      = jsonencode({
    Version = "2012-10-17",
    Statement = [
      {
        Effect   = "Allow",
        Action   = [
          "elasticache:DescribeCacheClusters",
          "elasticache:Connect",
          "elasticache:GetItem",          # Read from Redis
          "elasticache:PutItem",          # Write to Redis
          "elasticache:DeleteItem",       # Delete from Redis
          "elasticache:ListKeys",         # List keys in Redis
          "elasticache:BatchWriteItem",   # Batch operations
          "elasticache:BatchGetItem"      # Batch reads
        ],
        Resource = [
          "arn:aws:elasticache:${data.aws_region.current.name}:${data.aws_caller_identity.current.account_id}:cluster/${local.environment}-redis-cluster"
        ]
      }
    ]
  })
}


# Attach IAM Policy to ECS Task Role
resource "aws_iam_role_policy_attachment" "attach_redis_access" {
  role       = aws_iam_role.ecs_task_execution_role.name
  policy_arn = aws_iam_policy.redis_access_policy.arn
}
