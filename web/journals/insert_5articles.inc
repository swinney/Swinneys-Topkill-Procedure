<!-- insert_articles.inc -->
<?

// include "connect.inc";

$result_set = mysql( "swinney", "SELECT * FROM pending_articles WHERE status='2' ORDER BY time DESC limit 5" );


   echo "<H2><font color='gray'>5 Latest Entries</font></H2>";
// multiple rows, limit 5 latest
while ( $individual_row = mysql_fetch_object( $result_set ) ) {

$url = "http://swinney.org/journals/article.phtml?id=";
   echo "<font face='arial' size='4'><a href=\"$url$individual_row->article_id.txt\"><B>$individual_row->title</a></B> <font color='#FFFFFF'>by</font> <a href='$individual_row->web' target='new'>$individual_row->username</a><br><br> ";

}


?>

