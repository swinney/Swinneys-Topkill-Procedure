<!-- BEGIN next_article.inc -->
<?
// turn off errors if there is no database connect it wont dump shit.
error_reporting(0);

// we need the .txt separated off, we do this by exploding at the "." and taking temp[0]
$temp = explode(".", $id);

// first select, the username of the current article
$res1 = mysql ("$DB", "SELECT username FROM pending_articles WHERE article_id=$temp[0]");

// pull the row out into an array
$author = mysql_fetch_row($res1);

// second select, the article id previous to the current
$res2 = mysql ("$DB", "SELECT article_id FROM pending_articles WHERE article_id < $temp[0] AND username='$author[0]' AND status=2 ORDER BY article_id DESC LIMIT 1");
// fetch that out
$previous = mysql_fetch_row($res2);

// third select, the article id next to the current
$res3 = mysql ("$DB", "SELECT article_id FROM pending_articles WHERE article_id > $temp[0] AND username='$author[0]' AND status=2 ORDER BY article_id ASC LIMIT 1");

// fetch that out
$next = mysql_fetch_row($res3);


// if no set, then dont display, M'kay?
if (isset($previous[0])) {

echo " <P><TT><a href=\"article.phtml?id=$previous[0].txt\"><<</a> | ";
$addbar=1;
} else {

echo " <P><TT><< | ";

}


// same here
if (isset($next[0])) {

echo "<a href=\"article.phtml?id=$next[0].txt\">>></a></TT></P>";

} else {

echo " >></TT></P>";
}


// unset them all to irradicate confusion on later selects
unset($res1);
unset($res2);
unset($res3);
?>

<!-- END next_article.inc -->






