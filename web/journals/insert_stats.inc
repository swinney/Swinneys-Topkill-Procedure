<?

$articles = mysql_fetch_row ( mysql("$DB", "SELECT count(article_id) FROM articles" ) );
$comments = mysql_fetch_row ( mysql("$DB", "SELECT count(comment_id) FROM comments" ) );
$thoughts = mysql_fetch_row ( mysql("$DB", "SELECT count(comment_id) FROM thoughts" ) );
$pending = mysql_fetch_row ( mysql("$DB", "SELECT count(status) FROM pending_articles where status=0") );

echo "<BR><CENTER><TT>articles: $articles[0]; comments: $comments[0]; thoughts: $thoughts[0]; pending: $pending[0];</TT></CENTER><BR>";
?>