<?

// insert_userpages.inc/phtml

$res1 = mysql_query("SELECT * FROM articles_info WHERE user_id='".addslashes($user_id)."' AND status='2' ORDER BY time DESC" );



$url = "article.phtml?id=$d->article_id";

   echo "<h1>Journal Entries</h1>";
   echo "<P><a href='submit_article.phtml'>I want to contribute!</a></P>";

// multiple rows 
while ( $individual_row = mysql_fetch_object( $res1 ) ) {

// one row
//$individual_row = mysql_fetch_object( $res1 ); 

   echo "<table border=0 cellspacing=0 cellpadding=3><tr><td>"; 

   echo "<font face='arial' size='2'><a href=\"$url$individual_row->article_id\"><B>$individual_row->title</a></B> by <a href='$individual_row->web' target='new'>$individual_row->username</a><br> ";
   echo "$individual_row->blurb</font><br>";
   echo "<font face=\"arial\" size='1'>$individual_row->date "; 

$res2 = mysql_db_query("swinney", "SELECT * FROM comments WHERE article_id='$individual_row->article_id'");

$numrows =  mysql_num_rows($res2);

echo " | $numrows comments";

   echo "</td></tr></table>\n";

}


?>






