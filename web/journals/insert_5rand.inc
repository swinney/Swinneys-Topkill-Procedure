<!-- insert_5rand.inc -->
<?

// random?

$rand1 = dice( 1 , 1000 );
$rand2 = dice( 1 , 1000 );
$rand3 = dice( 1 , 1000 );
$rand4 = dice( 1 , 1000 );
$rand5 = dice( 1 , 1000 );
// echo "$rand1<BR>";

$res = mysql( "$DB", "SELECT article_id,username,title,date,web FROM pending_articles WHERE status='2' AND article_id=$rand1 OR article_id=$rand2 OR article_id=$rand3 OR article_id=$rand4 OR article_id=$rand5 ORDER BY time limit 5" );

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

   echo "<P>$username wrote ";
   echo "<a href=\"$url$article_id.txt\"><B>$title</a></B></P>\n";

}


/*
// multiple rows, limit 5 latest


while ( $individual_row = mysql_fetch_object( $res ) ) {

$url = "journals/article.phtml?id=";
   echo "<a href='$individual_row->web'>$individual_row->username</a> wrote ";
   echo "<a href=\"$url$individual_row->article_id.txt\"><B>$individual_row->title</a></B><BR><BR>\n";

}

*/

?>



