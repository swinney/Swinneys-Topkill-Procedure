<!--
$Id$
-->
<?

$res = mysql_query("SELECT article_id,username,web,date,title,blurb FROM articles_info WHERE status='2' ORDER BY time DESC limit 10" );

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

	$writes = array( 1 => 
			'writes',
			'pens',
			'scribes',
			'whips out',
			'jots',
			'notes',
			'scrawls',
			'scribbles',
			'drafts',
			'whips off',
			'makes another swinney with',
			'clarifies',
			'shares',
			'steals the narrative with',
			'makes a statement with',
			'howles',
			'enunciates with',
			'with forked tongue speaks',
			'defines the <I>rules of engagement</I> IN'
			);

	$word=count($writes);
	$num=dice(1,$word);


$url = "journals/article.phtml?id=";

   echo "<P>$username $writes[$num] ";
   echo "<a href=\"$url$article_id.txt\"><B>$title</a></B></P>\n";

}





?>

