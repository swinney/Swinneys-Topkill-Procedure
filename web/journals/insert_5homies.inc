<!-- $Id$ $Author$ $Date$ -->
<!-- insert_articles.inc -->
<?

// 

$res = mysql( "$DB", "SELECT username,title,article_id FROM articles_info WHERE status='2' AND $USERS ORDER BY time DESC limit 5" );

// multiple rows, limit 5 latest
while ( $individual_row = mysql_fetch_object( $res ) ) {

$url = "journals/article.phtml?id=";
   echo "<a href='$individual_row->web'>$individual_row->username</a> writes ";
   echo "<a href=\"$url$individual_row->article_id.txt\"><B>$individual_row->title</a></B><BR><BR>\n";

}


?>

