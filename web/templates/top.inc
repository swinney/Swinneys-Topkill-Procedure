<?
#####################################################
#$Id$
#####################################################
# top.inc - super hyper dynamic
# include file for all of swinney.org
# change this and change the world.
# Austin Swinney, of course.
# Thu Jul  5, 2001  7:54 AM
#####################################################

include "/sky/www/swinney.org/html/dev/journals/global.inc";
conn();
?>



<HTML>
<HEAD>
<TITLE><? echo TITLE. ": $title"; ?></TITLE>
<META NAME="ROBOTS" CONTENT="NOINDEX,NOFOLLOW">
<META NAME="keywords" CONTENT=" Austin Swinney ;">
<META HTTP-EQUIV="Expires" CONTENT="0">
<?
# style sheet for BCM
if (defined("WWW_ROOT"))

{

	echo "<link rel=\"stylesheet\" type=\"text/css\" href=\"" . WWW_ROOT . "/main.css\">";

}

?> 
</HEAD>
<BODY>

 
<!-- END PHP Dynamically Required File: top.inc -->
