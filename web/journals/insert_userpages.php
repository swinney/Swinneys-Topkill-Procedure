<?

// insert_userpages.inc/phtml
require_once("./global.php");

$res1 = mysql( "", "SELECT * FROM articles_info WHERE username="$username" AND status='2' OR status='3' ORDER BY time DESC" );

$url = "article.php?id=$d->article_id";

   echo "<h1>Articles</h1>";
   echo "<P><a href='submit_article.php'>I want to contribute!</a></P>";

// multiple rows 
while ( $individual_row = mysql_fetch_object( $res1 ) ) {

// one row
//$individual_row = mysql_fetch_object( $res1 ); 

   echo "<table border=0 cellspacing=0 cellpadding=3><tr><td>"; 

   echo "<font face='arial' size='2'><a href=\"$url$individual_row->article_id.txt\"><B>$individual_row->title</a></B> by <a href='$individual_row->web' target='new'>$individual_row->username</a><br> ";
   echo "$individual_row->blurb</font><br>";
   echo "<font face=\"arial\" size='1'>$individual_row->date "; 

$res2 = mysql_db_query("", "SELECT * FROM comments WHERE article_id='$individual_row->article_id'");

$numrows =  mysql_num_rows($res2);

echo " | $numrows comments";

   echo "</td></tr></table>\n";

}

?>

