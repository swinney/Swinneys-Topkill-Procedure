# MySQL dump 8.13
#
# Host: localhost    Database: swinney
#--------------------------------------------------------
# Server version	3.23.36


#
# Table structure for table 'categories'
#

CREATE TABLE categories (
  category_id int(11) NOT NULL auto_increment,
  name char(40) default NULL,
  PRIMARY KEY  (category_id)
) TYPE=MyISAM;


#
# Table structure for table 'comments'
#

CREATE TABLE comments (
  comment_id int(11) NOT NULL auto_increment,
  article_id int(11) NOT NULL default '0',
  timestamp timestamp(12) NOT NULL,
  username varchar(255) default 'anonymous',
  comment text,
  nature int(4) default NULL,
  status int(4) default '0',
  ip_addr text,
  PRIMARY KEY  (comment_id)
) TYPE=MyISAM;

#
# Table structure for table 'nature'
#

CREATE TABLE nature (
  nature_id int(4) NOT NULL auto_increment,
  nature varchar(20) default NULL,
  PRIMARY KEY  (nature_id)
) TYPE=MyISAM;

#
# Table structure for table 'pending_articles'
#

CREATE TABLE pending_articles (
  article_id int(11) NOT NULL auto_increment,
  username varchar(20) default NULL,
  web varchar(255) default NULL,
  date date default NULL,
  time int(11) default NULL,
  status int(11) default NULL,
  keywords varchar(100) default NULL,
  title varchar(255) default NULL,
  blurb varchar(255) default NULL,
  category bigint(20) default NULL,
  image tinyint(4) default NULL,
  ip_addr text,
  PRIMARY KEY  (article_id)
) TYPE=MyISAM;

#
# Table structure for table 'thoughts'
#

CREATE TABLE thoughts (
  comment_id int(11) NOT NULL auto_increment,
  timestamp timestamp(14) NOT NULL,
  username varchar(20) default 'nappy_sucka',
  thought text,
  status int(4) default NULL,
  ip_addr text,
  PRIMARY KEY  (comment_id)
) TYPE=MyISAM;




