<!-- insert_articles.inc -->
<?



$result_set = mysql( "", "SELECT * FROM pending_articles WHERE status='5' ORDER BY time DESC" );

$url = "article.phtml?id=$d->article_id";

   echo "<h1>Art</h1>";
   echo "<blockquote>my definition of art: if someone reacts to it as art, it's art, regardless of intent. if someone intends it to be art, it's art, regardless of reaction.   --10/13/00, <a href='http//elly.org/passion/' target='new'>elly.org</a></blockquote>";


// multiple rows 
while ( $individual_row = mysql_fetch_object( $result_set ) ) {

// one row
//$individual_row = mysql_fetch_object( $result_set ); 

   echo "<table border=0 cellspacing=0 cellpadding=3><tr><td>"; 

   echo "<font face='arial' size='2'><a href=\"$url$individual_row->article_id.txt\"><B>$individual_row->title</a></B> by <a href='$individual_row->web' target='new'>$individual_row->username</a><br> ";
   echo "$individual_row->blurb</font><br>";
   echo "<font face=\"arial\" size='1'>$individual_row->date</font><br> "; 
   echo "</td></tr></table>\n";
}


?>


