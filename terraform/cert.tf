# Reference the existing certificate
data "aws_acm_certificate" "so_cert" {
  domain      = "www.swinney.org"  # One of your domain names
  statuses    = ["ISSUED"]         # Only fetch valid certificates
  most_recent = true              # In case there are multiple matches
}

# Reference the Route 53 zone
data "aws_route53_zone" "so_zone" {
  zone_id = "Z0032769168B3R43N6PTC"
}

# The validation resources can be removed since the certificate 
# is already validated and exists