# MySQL dump 8.13
#
# Host: localhost    Database: swinney
#--------------------------------------------------------
# Server version	3.23.36

#
# Table structure for table 'articles_comments'
#

CREATE TABLE articles_comments (
  article_id int(11) default NULL,
  comments int(11) default NULL
) TYPE=MyISAM;

#
# Table structure for table 'articles_front'
#

CREATE TABLE articles_front (
  user_id int(11) NOT NULL default '0',
  article_id int(11) NOT NULL default '0'
) TYPE=MyISAM;

#
# Table structure for table 'articles_info'
#

CREATE TABLE articles_info (
  article_id int(11) NOT NULL auto_increment,
  user_id int(11) NOT NULL default '0',
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
# Table structure for table 'articles_text'
#

CREATE TABLE articles_text (
  article_id int(11) NOT NULL default '0',
  text mediumtext,
  PRIMARY KEY  (article_id)
) TYPE=MyISAM;

#
# Table structure for table 'articles_user'
#

CREATE TABLE articles_user (
  user_id int(11) NOT NULL auto_increment,
  username varchar(20) NOT NULL default '',
  most_recent int(11) default NULL,
  total_submitted int(11) default NULL,
  PRIMARY KEY  (user_id)
) TYPE=MyISAM;

#
# Table structure for table 'categories'
#

CREATE TABLE categories (
  cat_id int(3) NOT NULL auto_increment,
  name char(40) default NULL,
  level1 int(32) default NULL,
  PRIMARY KEY  (cat_id)
) TYPE=MyISAM;

#
# Table structure for table 'columnists'
#

CREATE TABLE columnists (
  first_name varchar(25) default NULL,
  last_name varchar(25) default NULL,
  email_addy varchar(40) default NULL
) TYPE=MyISAM;

#
# Table structure for table 'comments'
#

CREATE TABLE comments (
  comment_id int(11) NOT NULL auto_increment,
  article_id int(11) NOT NULL default '0',
  timestamp timestamp(12) NOT NULL,
  user_id int(11) NOT NULL default '0',
  username varchar(255) default 'anonymous',
  comment text,
  nature int(4) default NULL,
  chars int(11) NOT NULL default '0',
  to_user_id int(11) NOT NULL default '0',
  status int(4) default '0',
  ip_addr text,
  PRIMARY KEY  (comment_id)
) TYPE=MyISAM;

#
# Table structure for table 'email_list'
#

CREATE TABLE email_list (
  list_id int(11) NOT NULL auto_increment,
  email varchar(255) NOT NULL default '',
  PRIMARY KEY  (list_id)
) TYPE=MyISAM;

#
# Table structure for table 'insult_cat'
#

CREATE TABLE insult_cat (
  cat_id int(3) NOT NULL auto_increment,
  cat_name varchar(40) NOT NULL default '',
  tracking_method int(3) NOT NULL default '0',
  PRIMARY KEY  (cat_id)
) TYPE=MyISAM;

#
# Table structure for table 'insult_methods'
#

CREATE TABLE insult_methods (
  method_id int(3) NOT NULL auto_increment,
  method_name varchar(50) NOT NULL default '',
  PRIMARY KEY  (method_id)
) TYPE=MyISAM;

#
# Table structure for table 'links'
#

CREATE TABLE links (
  link_id int(11) NOT NULL auto_increment,
  username varchar(20) default NULL,
  timestamp timestamp(12) NOT NULL,
  status tinyint(4) default NULL,
  title varchar(50) default NULL,
  url varchar(255) default NULL,
  blurb varchar(255) default NULL,
  category int(20) default NULL,
  PRIMARY KEY  (link_id)
) TYPE=MyISAM;

#
# Table structure for table 'multi_articles'
#

CREATE TABLE multi_articles (
  multi_id int(8) NOT NULL default '0',
  article_id int(11) NOT NULL default '0'
) TYPE=MyISAM;

#
# Table structure for table 'multi_info'
#

CREATE TABLE multi_info (
  multi_id int(8) NOT NULL auto_increment,
  user_id int(8) NOT NULL default '0',
  title varchar(255) NOT NULL default 'no title',
  abstract text,
  PRIMARY KEY  (multi_id)
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
# Table structure for table 'perm_set'
#

CREATE TABLE perm_set (
  perm_id int(4) NOT NULL auto_increment,
  name char(40) NOT NULL default '',
  PRIMARY KEY  (perm_id)
) TYPE=MyISAM;

#
# Table structure for table 'search_words'
#

CREATE TABLE search_words (
  word_id int(11) NOT NULL auto_increment,
  word varchar(50) NOT NULL default '0',
  num_rows int(5) NOT NULL default '0',
  num_times int(4) NOT NULL default '0',
  ip_addr text NOT NULL,
  PRIMARY KEY  (word_id)
) TYPE=MyISAM;

#
# Table structure for table 'shorts'
#

CREATE TABLE shorts (
  article_id int(8) NOT NULL auto_increment,
  username varchar(40) NOT NULL default 'anonymous',
  text text,
  PRIMARY KEY  (article_id)
) TYPE=MyISAM;

#
# Table structure for table 'thoughts'
#

CREATE TABLE thoughts (
  comment_id int(11) NOT NULL auto_increment,
  timestamp timestamp(14) NOT NULL,
  user_id int(11) default '0',
  username varchar(20) default 'nappy_sucka',
  thought text,
  status int(4) default NULL,
  ip_addr text,
  PRIMARY KEY  (comment_id)
) TYPE=MyISAM;

#
# Table structure for table 'tmp'
#

CREATE TABLE tmp (
  article_id int(11) NOT NULL default '0'
) TYPE=MyISAM;

#
# Table structure for table 'user'
#

CREATE TABLE user (
  user_id int(11) NOT NULL auto_increment,
  username varchar(20) NOT NULL default '',
  email text NOT NULL,
  password text NOT NULL,
  ip_addr text NOT NULL,
  confidence int(3) default '0',
  PRIMARY KEY  (user_id)
) TYPE=MyISAM;

#
# Table structure for table 'user_bozo'
#

CREATE TABLE user_bozo (
  user_id int(11) NOT NULL default '0',
  bozo_id int(11) default NULL,
  bozoname varchar(20) NOT NULL default 'ass bastard',
  PRIMARY KEY  (user_id,bozoname)
) TYPE=MyISAM;

#
# Table structure for table 'user_perm'
#

CREATE TABLE user_perm (
  order_id int(11) NOT NULL auto_increment,
  user_id int(11) default '0',
  perm int(1) NOT NULL default '0',
  PRIMARY KEY  (order_id)
) TYPE=MyISAM;

#
# Table structure for table 'user_settings'
#

CREATE TABLE user_settings (
  user_id int(11) NOT NULL default '0',
  noise_filter int(11) NOT NULL default '0'
) TYPE=MyISAM;

#
# Table structure for table 'user_total'
#

CREATE TABLE user_total (
  user_id int(11) NOT NULL default '0',
  username varchar(20) default NULL,
  num_articles int(11) default NULL,
  PRIMARY KEY  (user_id)
) TYPE=MyISAM;

