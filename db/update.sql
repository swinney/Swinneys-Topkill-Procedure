alter table user_bozo add bozo_id int(11) after user_id;

ALTER TABLE articles_info 
ADD num_comments int(5) 
DEFAULT '0' NOT NULL 
AFTER ip_addr;
