<? 
// $Id$
require_once("../global.php");
include_once(INCDIR ."/top.inc");
include_once(INCDIR ."/admin_nav.inc");
?>

<TABLE border=1 cellspacing=0 cellpading=0>
<TR>
<TD>comment_id</TD>
<TD>edit</TD>
<TD>username</TD>
<TD>comment</TD>
</TR>
<?

$previous=1;

$res = mysql_query("select * from comments where article_id=$article_id order by comment_id DESC");

while ( $d = mysql_fetch_object ($res) ) {
$comment_id = $d->comment_id;
$username = $d->username;
$comment = $d->comment;
$article_id = $d->article_id;

echo "<TR><TD valign='top'>\n";
echo "<a href='http://swinney.org/journals/article.php?id=$article_id.txt#$comment_id'>($article_id) $comment_id</a></TD>\n";
echo "<TD valign='top'><a href='edit_comments.php?article_id=$article_id&comment_id=$comment_id&previous=$previous'>=>edit<=</a></TD>";
echo "<TD valign='top'>$username</TD><TD>".stripslashes($comment)."</TD></TR>";

}
echo "</TABLE>";
include_once(INCDIR ."/footer.inc");
?>
