<!-- insert_articles.inc -->
<?

// 

$res = mysql( "$DB", "SELECT * FROM pending_articles WHERE status='2' ORDER BY time DESC limit 5" );

// multiple rows, limit 5 latest
while ( $individual_row = mysql_fetch_object( $res ) ) {

$url = "journals/article.phtml?id=";
   echo "<a href='$individual_row->web'>$individual_row->username</a> writes ";
   echo "<a href=\"$url$individual_row->article_id.txt\"><B>$individual_row->title</a></B><BR><BR>\n";

}


?>

