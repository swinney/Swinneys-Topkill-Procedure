Given this user table in mysql:

       Table: user
Create Table: CREATE TABLE `user` (
  `user_id` int NOT NULL AUTO_INCREMENT,
  `username` varchar(20) NOT NULL DEFAULT '',
  `email` text NOT NULL,
  `password` text NOT NULL,
  `ip_addr` text NOT NULL,
  `last` datetime DEFAULT NULL,
  `language` varchar(40) NOT NULL DEFAULT 'en',
  `city` varchar(30) NOT NULL DEFAULT 'Elko',
  `state` varchar(30) NOT NULL DEFAULT 'Nevada',
  `country` char(2) NOT NULL DEFAULT 'US',
  PRIMARY KEY (`user_id`)
) ENGINE=MyISAM AUTO_INCREMENT=991 DEFAULT CHARSET=latin1

And given this existing registration processing script:  process_registration.php

Update the script to use prepared statements to prevent SQL injection attacks.  The script should also validate the email address and password to ensure they meet the following requirements:

- Email address must be a valid email address
- Password must be at least 8 characters long and contain at least one uppercase letter, one lowercase letter, one number, and one special character
- use Google Captcha V2 to prevent bots from registering
- make the code PHP8 compatible
- make sure the code is secure and not vulnerable to any attacks
- make sure the code is using the best practices
- make sure the code is object-oriented
- make sure the code is clean and easy to read
- make sure the code is well commented
- make sure the code is tested and 100% working
- make sure the code is PEP8 compliant


ALTER TABLE `user` 
ADD COLUMN `password_reset_token` VARCHAR(255) DEFAULT NULL, 
ADD COLUMN `token_expiry` DATETIME DEFAULT NULL;
