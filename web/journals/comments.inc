
<?
// comments.inc


// this is set to determine header() in process_edit_comments.phtml

echo "<!-- previous: $previous -->\n";

while ( $d = mysql_fetch_object ($res) ) {
$comment_id = $d->comment_id;
$username = $d->username;
$comment = $d->comment;
$article_id = $d->article_id;

$res2 = mysql_query ( "SELECT username,title FROM articles_info WHERE article_id=$article_id");
$row = mysql_fetch_row($res2);

echo "<TABLE border=1 cellspacing=0 cellpading=0 width='100%'>";
echo "<TR><TD valign='top' bgcolor=#999999>\n";
echo "$username on \"<a href='article.phtml?id=$article_id.txt#$comment_id'>$row[1]</A>\" by <a href='userpages.phtml?username=$row[0]'>$row[0]</a></TD></TR>";
echo "<TR><TD>".stripslashes($comment)."</TD></TR></TABLE>";

}
?>




































