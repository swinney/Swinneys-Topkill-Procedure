variable "NGINX_HOST" {
  type = string
  default = "localhost"
}

variable "URLBASE" {
  type = string
  default = "http://locahost"
}

variable "PHP_VERSION" {
  type = string
  default = "8.3"
}

variable "MYSQL_VERSION" {
  type = string
  default = null
}

variable "DB_HOST" {
  type = string
  default = null
}

variable "DB_NAME" {
  type = string
  default = "swinney"
}

# Additional database configuration variables
variable "DB_USER" {
  type = string
  default = "swindev"  # You can override this in .tfvars
}

variable "DB_PASSWD" {
  type = string
  sensitive = true
  default = null
}

variable "DB_ENGINE" {
  type = string
  default = "mysql"
}

variable "DB_PORT" {
  type = number
  default = 3306
}

variable "DB_INSTANCE_IDENTIFIER" {
  type = string
  default = "swindev"
}

variable "AWS_REGION" {
  type = string
  default = "us-west-2"
}

variable "AWS_ACCOUNT_ID" {
  type = string
  default = "905418316682"
}

variable "AWS_PROFILE" {
  type = string
  default = "default"
}

variable "AWS_DEFAULT_REGION" {
  type = string
  default = "us-west-2"
}
