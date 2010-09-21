<?
#####################################
# $Id$
# top.inc - super hyper dynamic
# include file for all of swinney.org
# change this and change the world.
# Austin Swinney, of course.
# Thu Jul  5, 2001  7:54 AM
# tweaked by James Home on 020010921
# with no small amount of inspiration
# from Gavin Cruickshank.
#####################################
session_unregister("back_to");
$url = split('/',$SCRIPT_NAME);
$auth_these=array(
		  "submit_comment.phtml",
		  "submit_article.phtml",
		  "vip",
		  "madmin",
		  "admin",
		  );

$yes = array_intersect($url,$auth_these);
$num_intersect = count($yes);

if($num_intersect>0) {
  $thisurl=urlencode($thisurl);
  if ($authenticated_username && !$authenticated_user_id) {
    $authenticated_user_id=get_user_id($authenticated_username);
  }
  is_auth($authenticated_username,$authenticated_user_id,$thisurl);
  // should not need to exit, is_auth will exit if necessary.
}

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<!-- <? echo $HTTP_REFERER; ?> -->
<!-- <? echo $REQUEST_URI; ?> -->
<!-- <? echo $authenticated_username ." / ". $authenticated_user_id; ?> -->
<!-- you madame of the internet,  -->
<!-- you gigolo  of the world,    -->
<!-- don't forget to breathe.     -->
<!-- EVERYTHING {c} Swinney.org   -->
<!-- s.o is a technical product of
         (in order of appearance):

Austin Swinney
"I want a ..."
programmer   

Elly Millican
"i can't believe more people don't do this"
early adopter

Steve Simizis
Hint: double soy mocha with a shot of vanilla
atari system administrator

Brian Mosely
"Eat a dong."
programmer/atari database administrator

James Home
"I learned it from you!"
artist in residence
-->

<html>
<head>
<meta name="verify-v1" content="nKFmiauH7M4SMFMItPEHTDSrz2Ca60IlV1TxnnllifE=" >
<title>SWINNEY LIVES!! </title>

<meta http-equiv="expires" content="0">
<meta name="keywords" content=" austin swinney, <? echo $a_keywords;?> ;">
<link rel="stylesheet" type="text/css" href="<? echo CSS_URL; ?>"> 
<link rel="shortcut icon" href="http://www.swinney.org/favicon.ico">
<script src="http://www.google-analytics.com/urchin.js"
type="text/javascript">
</script>
<script type="text/javascript">
_uacct = "UA-689669-2";
_udn="swinney.org";
urchinTracker();
</script>
<script type="text/javascript" language="JavaScript" src="<? echo URLBASE; ?>/journals/rollover.js"></script>
<script type="text/javascript" language="JavaScript">
//<!--
MM1 = new rollover("ithoughtit","<? echo URLBASE; ?>/journals/img/ithoughtit.gif", "<? echo URLBASE; ?>/journals/img/ithoughtit-over.gif", "ithoughtit"); 
MM2 = new rollover("articles","<? echo URLBASE; ?>/journals/img/articles.gif", "<? echo URLBASE; ?>/journals/img/articles-over.gif", "articles"); 
MM3 = new rollover("comments","<? echo URLBASE; ?>/journals/img/comments.gif", "<? echo URLBASE; ?>/journals/img/comments-over.gif", "comments"); 
MM4 = new rollover("faq","<? echo URLBASE; ?>/journals/img/faq.gif", "<? echo URLBASE; ?>/journals/img/faq-over.gif", "faq"); 
MM5 = new rollover("submit","<? echo URLBASE; ?>/journals/img/submit.gif", "<? echo URLBASE; ?>/journals/img/submit-over.gif", "submit"); 
MM6 = new rollover("register","<? echo URLBASE; ?>/journals/img/register.gif", "<? echo URLBASE; ?>/journals/img/register-over.gif", "register"); 
MM7 = new rollover("login","<? echo URLBASE; ?>/journals/img/login.gif", "<? echo URLBASE; ?>/journals/img/login-over.gif", "login"); 
MM8 = new rollover("settings","<? echo URLBASE; ?>/journals/img/settings.gif", "<? echo URLBASE; ?>/journals/img/settings-over.gif", "settings"); 
MM9 = new rollover("logout","<? echo URLBASE; ?>/journals/img/logout.gif", "<? echo URLBASE; ?>/journals/img/logout-over.gif", "logout"); 
MM10 = new rollover("search","<? echo URLBASE; ?>/journals/img/search.gif", "<? echo URLBASE; ?>/journals/img/search-over.gif", "search"); 
MM11 = new rollover("addcomment1","<? echo URLBASE; ?>/journals/img/addcomment.gif", "<? echo URLBASE; ?>/journals/img/addcomment-over.gif", "addcomment1"); 
MM12 = new rollover("addcomment2","<? echo URLBASE; ?>/journals/img/addcomment.gif", "<? echo URLBASE; ?>/journals/img/addcomment-over.gif", "addcomment2"); 
MM13 = new rollover("isaidit","<? echo URLBASE; ?>/journals/img/isaidit.gif", "<? echo URLBASE; ?>/journals/img/isaidit-over.gif", "isaidit"); 
//-->
</script>

</head>

<body bgcolor="#cccccc" link="#000099" vlink="#330066" alink="#ff0000"
marginwidth=0 marginheight=0 topmargin=0 leftmargin=0>

<!-- END PHP Dynamically Required File: top.inc -->







