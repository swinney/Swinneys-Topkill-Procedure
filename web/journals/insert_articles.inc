<!-- insert_articles.inc -->
<?

include "connect.inc";

$res1 = mysql( "swinney", "SELECT * FROM pending_articles WHERE status='2' ORDER BY time DESC LIMIT 25" );



$url = "article.phtml?id=$d->article_id";

   echo "<h1>Last 25 Entries</h1>";
   echo "<P><a href='submit_article.phtml'><strong>I want to write</strong></a></P>";

// multiple rows 
while ( $individual_row = mysql_fetch_object( $res1 ) ) {

// one row
//$individual_row = mysql_fetch_object( $res1 ); 

   echo "<table border=0 cellspacing=0 cellpadding=3><tr><td>"; 

   echo "<font face='arial' size='2'><a href=\"$url$individual_row->article_id.txt\"><B>$individual_row->title</a></B> by <a href='$individual_row->web' target='new'>$individual_row->username</a><br> ";
   echo "$individual_row->blurb</font><br>";
   echo "<font face=\"arial\" size='1'>$individual_row->date "; 

$res2 = mysql_db_query("swinney", "SELECT * FROM comments WHERE article_id='$individual_row->article_id'");

$numrows =  mysql_num_rows($res2);

echo " | $numrows comments";

   echo "</td></tr></table>\n";

}


?>






