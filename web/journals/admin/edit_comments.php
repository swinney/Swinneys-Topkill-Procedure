<?
// $Id$
include("../global.php");
include(INCDIR ."/top.inc");

/* ---------------------------------------------------------------------------
   edit_comments.php // this is for editing comments // austin swinney, 2001

  related tables:

  mysql> desc comments
      -> ;
  +------------+---------------+------+-----+-----------+ 
  | Field      | Type          | Null | Key | Default   |
  +------------+---------------+------+-----+-----------+
  | comment_id | int(11)       |      | PRI | 0         | auto_increment |
  | article_id | int(11)       |      |     | 0         |
  | timestamp  | timestamp(12) | YES  |     | NULL      |
  | username   | varchar(255)  | YES  |     | anonymous |
  | comment    | text          | YES  |     | NULL      |
  | nature     | int(4)        | YES  |     | NULL      |
  | status     | int(4)        | YES  |     | 0         |
  +------------+---------------+------+-----+-----------+
  7 rows in set (0.00 sec)

  ---------------------------------------------------------------------------*/


$res = mysql_query("SELECT comment_id, article_id, username, comment, nature, timestamp,status FROM comments WHERE comment_id=$comment_id");



$comment_id = mysql_result($res,0,0);
$article_id = mysql_result($res,0,1);
$username   = mysql_result($res,0,2);
$comment    = stripslashes(mysql_result($res,0,3));
$nature     = mysql_result($res,0,4);
$timestamp  = mysql_result($res,0,5);
$status     = mysql_result($res,0,6);
   echo "<CENTER>";
   echo <<<EOT
<H1>NO COMMENTS SHOULD BE DELETED</H1>
<P>this is for editing bad html and image tags.  nothing more.<BR>  
if for nebulous editorial purposes it should be removed, <BR>
USE THE STATUS drop down menu.</P>

<FORM METHOD='post' ACTION='process_edit_comments.php'>
<input type='hidden' name='article_id' value='$article_id'>
<input type='hidden' name='comment_id' value='$comment_id'>
<input type='hidden' name='timestamp' value=$timestamp>
<input type='hidden' name='previous' value='$previous'>
<TABLE WIDTH=600 border=0>
<TR WIDTH=150><TD valign='top'><TABLE align='top'>
<TR><TD>comment id: $comment_id</TD></TR>
<TR><TD>article id: $article_id</TD></TR>
<TR><TD>username: $username</TD></TR>
<TR><TD>nature: $nature</TD></TR>
<TR><TD>timestamp: $timestamp</TD></TR>
<TR><TD>
EOT;
    echo "<P><b>Status : </b> <select name='status'>";
    if ( $status == 0 ) {
      echo "<option value='0' selected>Active";
    } else if ( $status == 1 ) {
      echo "<option value='1' selected>Trash";
    }
    echo "<option>---\n";
    echo "<option value='0'>Active\n";
    echo "<option value='1'>Trash\n";
    echo "\n</select>\n";

echo <<<EOT
</TD></TR>
</TABLE></TD><TD>
<TEXTAREA TYPE=text NAME=comment COLS=50 ROWS=20 WRAP=virtual>$comment</TEXTAREA>
</TD></TR></TABLE>
<INPUT TYPE=SUBMIT></FORM></TABLE>
<!-- previous: $previous -->
EOT;
?>

</CENTER>
</BODY>
</HTML>














