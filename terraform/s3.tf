# # S3 Buckets for Images
# resource "aws_s3_bucket" "images_bucket" {
#   count = length(var.environments)
#   bucket = "${var.environments[count.index]}-images-bucket"

#   lifecycle {
#     prevent_destroy = true
#     ignore_changes  = [bucket]
#   }

#   tags = {
#     Name        = "${var.environments[count.index]}-images-bucket"
#     Environment = var.environments[count.index]
#   }
# }

# resource "aws_s3_bucket_acl" "images_bucket_acl" {
#   count = length(var.environments)
#   bucket = aws_s3_bucket.images_bucket[count.index].id
#   acl    = "private"
# }

# resource "null_resource" "s3_cleanup" {
#   count = length(var.environments)
  
#   provisioner "local-exec" {
#     command = "aws s3 rm s3://${aws_s3_bucket.images_bucket[count.index].bucket} --recursive"
#   }

#   depends_on = [aws_s3_bucket.images_bucket]
# }
