<?

$articles = mysql_fetch_row ( mysql_query ( "SELECT count(article_id) FROM articles_info" ) );
$comments = mysql_fetch_row ( mysql_query ( "SELECT count(comment_id) FROM comments" ) );
$thoughts = mysql_fetch_row ( mysql_query ( "SELECT count(comment_id) FROM thoughts" ) );
$pending = mysql_fetch_row ( mysql_query ( "SELECT count(status) FROM articles_info where status=0") );

echo "<BR><CENTER><TT>articles: $articles[0]; comments: $comments[0]; thoughts: $thoughts[0]; pending: $pending[0];</TT></CENTER><BR>";
?>
