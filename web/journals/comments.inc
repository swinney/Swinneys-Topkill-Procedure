<?
# $Id$

// what table are you paginating?
$table="comments";

// what page would you like to return?
$return="$PHP_SELF";

//No Page Number? Set it to Page 1 then
if(!$page_num || $page_num < 1) { 
        $page_num = 1;
}

//How many pages per page will be displayed...
$per_page = 20;

//Set the page start variable...
$page_start = ($page_num-1) * $per_page;


 
//Do a number query to see how many results match the category...
$num_res = mysql_query ( "SELECT count(*) as num_articles FROM $table WHERE status='0' ORDER BY timestamp DESC");
$num_object = MYSQL_FETCH_OBJECT($num_res);
$num_of_results = $num_object->num_articles;

$res = mysql_query ( "SELECT username,comment_id,comment,article_id FROM $table WHERE status='0' ORDER BY timestamp DESC limit $page_start,$per_page");

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
             print "<TT><a href=\"$return?&page_num=$page_back\"><<</a> |";


     } 

  
     if($page_num < $num_of_pages) { 
             print " <a href=\"$return?page_num=$page_forward\">>></a></TT>";
     } 

     if($page_num == $num_of_pages) {
             print ">></TT>";
     }

 echo "</P>";

}

echo "<!-- previous: $previous -->\n";

while ( $d = mysql_fetch_object ($res) ) {

$comment_id = $d->comment_id;
$username   = stripslashes($d->username);
$comment    = stripslashes($d->comment);
$article_id = $d->article_id;

$res2 = mysql_query ("SELECT username,title FROM articles_info WHERE article_id=$article_id");
$row = mysql_fetch_row($res2);
echo "\n<BR>";
echo "\n<P>$username on \"<a href='article.phtml?id=$article_id.txt#$comment_id'>$row[1]</A>\" by <a href='userpages.phtml?username=$row[0]'>$row[0]</a></P>";
echo "<P>$comment</P>";

}
?>







