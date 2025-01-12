# Add AWS Secrets Manager resource for sensitive data
data "aws_secretsmanager_secret" "db_config" {
  name = "${local.environment}/mysql/master/config"
}

data "aws_secretsmanager_secret_version" "current" {
  secret_id = data.aws_secretsmanager_secret.db_config.id
}

# resource "aws_secretsmanager_secret_version" "db_config" {
#   secret_id = aws_secretsmanager_secret.db_config.id
#   secret_string = jsonencode({
#     username              = "swindev"
#     password             = "xxxxxxx"
#     engine               = "mysql"
#     host                 = "swindev.cxig24isc9ar.us-west-2.rds.amazonaws.com"
#     port                 = 3306
#     dbname               = "swinney"
#     dbInstanceIdentifier = "swindev"
#   })
# }