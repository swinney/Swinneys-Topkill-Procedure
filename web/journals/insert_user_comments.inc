<?
#$Id$

#first do pagination

// what table are you paginating?
$table="comments";

//No Page Number? Set it to Page 1 then
if(!$page_num || $page_num < 1) { 
        $page_num = 1;
}

//How many pages per page will be displayed...
$per_page = 30;

//Set the page start variable...
$page_start = ($page_num-1) * $per_page;


 
//Do a number query to see how many results match the category...
$num_res = mysql_query ( "SELECT count(*) as num_articles FROM $table WHERE status='0' AND username LIKE '%$username%' ORDER BY timestamp DESC");
$num_object = MYSQL_FETCH_OBJECT($num_res);
$num_of_results = $num_object->num_articles;


$query2="SELECT username,comment_id,comment,article_id FROM $table WHERE status='0' AND username LIKE '%$username%' ORDER BY timestamp DESC limit $page_start,$per_page";

$query = "select comments.comment_id,comments.article_id,comments.username,articles_info.title from comments, articles_info where comments.article_id=articles_info.article_id AND comments.username like '%". addslashes($username) ."%' order by comment_id DESC limit $page_start,$per_page";


$res2 = mysql_query ($query);

// Find out how many pages there are going to be
// number of results returned divided by the number per page displayed
$num_of_pages = $num_of_results/$per_page; 

// Find out if the num_of_pages was a decimal.. Can't have 2.1 pages...
$remainders = $num_of_results%$per_page; 


if($remainders != 0){ //If is was a decimal, turn it into an integer and add 1 to it...
       $num_of_pages = intval($num_of_pages) + 1;
}

$page_back = $page_num - 1;
$page_forward = $page_num + 1;


//while ($row = mysql_fetch_object($res)) {
if (isset($res)) {

$url = "article.phtml?id=$d->article_id";



   echo "<P>";

     if($page_num == 1){
            print "<TT><< |";
     }


     if($page_num > 1){
	     print "<TT><a href=\"$PHP_SELF?username=$username&page_num=$page_back\"><<</a> |";


     } 

  
     if($page_num < $num_of_pages) { 
             print " <a href=\"$PHP_SELF?username=$username&page_num=$page_forward\">>></a></TT>";
     } 

     if($page_num == $num_of_pages) {
             print ">></TT>";
     }

 echo "</P>";

}


echo "<h2>user involved comments</h2>\n";
echo "\n<OL>";

$res = mysql_query($query);
$num = mysql_num_rows($res);
echo "\n<P>number of returns: $num</P>";

while ($d=mysql_fetch_object($res2)) {
        $article_id=$d->article_id;
	$comment_id=$d->comment_id;
        $title=$d->title;
        $username=$d->username;

	if ($title==$last) {
		echo "... sez <a href=\"article.phtml?id=$article_id#$comment_id\">$username</a>";
	} else {
	
        echo "\n<LI><P><a href=\"article.phtml?id=$article_id\">$title</a><BR>";
	echo "\n sez <a href=\"article.phtml?id=$article_id#$comment_id\">$username</a>";

	}

	$last=$title;
}

echo "\n</OL>";

?>
