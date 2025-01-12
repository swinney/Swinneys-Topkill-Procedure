# Load Balancer
resource "aws_lb" "so_app_lb" {
  name               = "${local.environment}-lb"
  load_balancer_type = "application"
  security_groups    = [aws_security_group.lb_sg.id]
  subnets = [
    aws_subnet.swindev_public_subnet_1.id,  # Subnet in AZ1
    aws_subnet.swindev_public_subnet_2.id   # Subnet in AZ2
  ]
  enable_deletion_protection = false
}

# Security Group for ALB
resource "aws_security_group" "lb_sg" {
  name        = "${local.environment}-lb-sg"
  description = "Allow HTTP and HTTPS traffic to ALB"
  vpc_id      = aws_vpc.swindev_ecs_vpc.id

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

# Target Group for ECS Service
resource "aws_lb_target_group" "so_app_target_group" {
  name        = "${local.environment}-so-app-tg"
  port        = 80
  protocol    = "HTTP"
  vpc_id      = aws_vpc.swindev_ecs_vpc.id
  target_type = "ip" # Required for Fargate

  health_check {
    path                = "/"
    protocol            = "HTTP"
    matcher             = "200-499"
    interval            = 300
    timeout             = 60
    healthy_threshold   = 2
    unhealthy_threshold = 10
  }
}

# HTTPS Listener
resource "aws_lb_listener" "https_listener" {
  load_balancer_arn = aws_lb.so_app_lb.arn
  port              = 443
  protocol          = "HTTPS"
  ssl_policy        = "ELBSecurityPolicy-2016-08"
  certificate_arn = data.aws_acm_certificate.so_cert.arn

  default_action {
    type             = "forward"
    target_group_arn = aws_lb_target_group.so_app_target_group.arn
  }
}

resource "aws_route53_record" "dev_swinney" {
   zone_id = "Z0032769168B3R43N6PTC"  # Hosted zone for swinney.org
  name    = "dev.swinney.org"
  type    = "A"

  alias {
    name                   = aws_lb.so_app_lb.dns_name
    zone_id                = aws_lb.so_app_lb.zone_id
    evaluate_target_health = true
  }
}
