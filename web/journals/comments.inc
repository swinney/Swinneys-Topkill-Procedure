<?
# $Id$
// comments.inc
// this is set to determine header() in process_edit_comments.phtml

echo "<!-- previous: $previous -->\n";

while ( $d = mysql_fetch_object ($res) ) {

$comment_id = $d->comment_id;
$username   = stripslashes($d->username);
$comment    = stripslashes($d->comment);
$article_id = $d->article_id;

$res2 = mysql_query ("SELECT username,title FROM articles_info WHERE article_id=$article_id");
$row = mysql_fetch_row($res2);
echo "\n<BR>";
echo "\n<P>$username on \"<a href='article.phtml?id=$article_id.txt#$comment_id'>$row[1]</A>\" by <a href='userpages.phtml?username=$row[0]'>$row[0]</a></P>";
echo "<P>$comment</P>";

}
?>




































