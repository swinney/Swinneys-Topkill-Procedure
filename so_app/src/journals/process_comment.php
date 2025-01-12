<?
#$Id$

require_once("./global.php");

// get the users ip address.  maybe this is uncool, but i think it is a
// necessary precaution.  like dont i want to know who the person is who
// tries to send malicious unix commands in to the thoughts database?

// get the ip number of the user
$ip_addr = getenv ("REMOTE_ADDR"); 

$article_id = explode (".", $article_id);

$article_id = $article_id[0];

  if ( $username == "" ) {
      $error_msg = "No one's a nobody on Swinney.org.  Enter your name.";
      session_register("error_msg");
      include("./submit_comment.php");
  }

  if ( $username == "name" ) {
      $error_msg = "Names are nice, but you should get your own.";
      session_register("error_msg");
      include("./submit_comment.php");
  }

  if ( $comment == "" ) {
      $error_msg = "Please speak louder, I can't hear you.";
      session_register("error_msg");
      include("./submit_comment.php");
  }

  if ( $comment == "comment" ) {
      $error_msg = "Commenting on this site is not like some other cultures.  Less is not more.";
      session_register("error_msg");
      include("./submit_comment.php");
  }

  if (!$nature) {
    $nature=0;
  }

  if (!$user_id) {
    $user_id=0;
  }
  if (!$user_id) {
    $user_id="0";
  }

$username=addslashes("$username");
$comment=addslashes("$comment");
$ip_addr=addslashes("$ip_addr");
$char=strlen($comment);

/*
 * moseley stlye error block.
 * -austin, Tue Mar  5, 2002  9:34 AM
 */

if (!$article_id) {
  $error_msg .= "<P>you dont have an article_id.</P>";
  if (!$_SESSION['authenticated_user_id']) {
    $error_msg .= "<P>you dont have an authenticated_user_id.  try logging out and logging back in.  logging in sets this.</P>";
    if (!$username) {
      $error_msg .= "<P>you dont have an username.  this is not authenticated, you need to put one in the form field.</P>";
      if (!$comment) {
        $error_msg .= "<P>you dont have an comment.  what are you trying to pull?  do we pay you?  you are fired!</P>";
	if (!$nature) {
	  $nature = 0;
	  if (!$char) {
	    $error_msg .= "<P>you dont have a char (character count).  this is either a program error, or you didnt write anything.  bastard.</P>";
	    if (!$to_user) {
	      $to_user=0;
	      if (!$ip_addr) {
$error_msg .= "<P>you dont have an ip address for us.  what is up with that?  im not sure, but i dont trust that look in your eye.  GUARDS, SIEZE HIM!</P>";
	      }
	    }
	  }
	}
      }
    }
  }
}


$query=<<<EOT
INSERT INTO comments 
     VALUES (
	     NULL,
	     $article_id,
	     NULL,
             $_SESSION['authenticated_user_id'],
	     "$username",
	     "$comment",
	      $nature,
	      $char,
	      $to_user,
	      0,
	     "$ip_addr",
	     "$language"
              )
EOT;

$res = mysql_query($query) or die("error inserting comment: $query"); 

$query=<<<EOT
update articles_info set num_comments=(num_comments+1) WHERE article_id=$article_id
EOT;
$res = mysql_query($query) or die("error inserting comment: $query"); 
if ($last_lang!=$language) {
    if (!$last_lang) {
      session_register("last_lang",$language);
    }
  $last_lang=$language;
}
// this is for elly's cellphone
// mail("ellys_cellphone@swinney.org", "comment: $username on $article_id", "$nature", "$comment"); 
header ("Location: article.php?id=$article_id");
?>










