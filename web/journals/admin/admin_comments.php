<? 
#$Id$
$title="Administrate Comments";
require_once("../global.php");
include_once(INCDIR ."/top.inc");
include_once(INCDIR ."/swinney.req");
?>


<center>
<p class="subheader">
<a href='index.php'>firebird</a> | 
<a href='listcontent.php'>articles</a> | 
<b>comments</b> | 
<a href='users.php'>users</a>
</p>
</center>

<table cellpadding=4 cellspacing=0 border=1 align=center width="98%">
<TR>
<TD nowrap><b>Comment ID</b></TD>
<TD><b>Edit</b></TD>
<TD><b>Username</b></TD>
<TD><b>Comment</b></TD>
</TR>
<?


// this is set to determine header() in process_edit_comments.php
$previous=0;
echo "<!-- previous: $previous -->\n";

$res = mysql_query("select comment_id,username,comment,article_id from comments where status=0 order by comment_id DESC limit 20");

while ( $d = mysql_fetch_object ($res) ) {

$comment_id = $d->comment_id;
$username = $d->username;
$comment = $d->comment;
$article_id = $d->article_id;

echo "<TR><TD valign='top'>\n";
echo "<a href='../article.php?id=$article_id.txt#$comment_id'>($article_id) $comment_id</a></TD>\n";
echo "<TD valign='top'><a href='edit_comments.php?comment_id=$comment_id&previous=$previous'>=>edit<=</a></TD>";
echo "<TD valign='top'>$username</TD><TD>".stripslashes($comment)."</TD></TR>";

}
?>
</TABLE>
</BODY>
</HTML>




















