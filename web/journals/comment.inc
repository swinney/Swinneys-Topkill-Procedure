<?
// comment.inc

include "connect.inc";
echo "<TABLE border=0 cellspacing=0 cellpading=0>";

// this is set to determine header() in process_edit_comments.phtml
$previous=0;
echo "<!-- previous: $previous -->\n";

// $res = mysql("$DB", "select * from comments order by article_id DESC limit 20");

$res = mysql("$DB", "select * from comments order by comment_id DESC limit 20");

while ( $d = mysql_fetch_object ($res) ) {
$comment_id = $d->comment_id;
$username = $d->username;
$comment = $d->comment;
$article_id = $d->article_id;

$res2 = mysql("$DB", "SELECT username,title FROM pending_articles WHERE article_id=$article_id");
$row = mysql_fetch_row($res2);

echo "<TR><TD valign='top' colspan=3>\n";
echo "$username on \"<a href='article.phtml?id=$article_id.txt#$comment_id'>$row[1]</A>\" by <a href='userpages.phtml?username=$row[0]'>$row[0]</a></TD></TR>";
echo "<TR><TD COLSPAN=2></TD><TD>".stripslashes($comment)."</TD></TR></TABLE>";

}
?>























