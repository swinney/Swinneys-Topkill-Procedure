<!-- insert_articles.inc -->
<?

// 

$res = mysql( "$DB", "SELECT article_id,username,web,date,title,blurb FROM pending_articles WHERE status='2' ORDER BY time DESC limit 10" );

// multiple rows, limit 10 latest
while ( $d = mysql_fetch_object( $res ) ) {

$article_id=$d->article_id;
$username=$d->username;
$web=$d->web;
$date=$d->date;
$title=$d->title;
$blurb=$d->blurb;



if ($web != "") {
	$username="<a href='".$web."'> ".stripslashes($username)."</a>";
}



$url = "journals/article.phtml?id=";

   echo "<P>$username writes ";
   echo "<a href=\"$url$article_id.txt\"><B>$title</a></B></P>\n";

}





?>

