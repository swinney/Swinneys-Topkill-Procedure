resource "aws_security_group" "rds_sg" {
  name   = "${local.environment}-rds-sg"
  vpc_id = aws_vpc.swindev_ecs_vpc.id
}

data "aws_db_instance" "existing" {
  db_instance_identifier = "swindev"
}