<?
#$Id$

if(!$page_num || $page_num < 1) { //No Page Number? Set it to Page 1 then...
        $page_num = 1;
}

//How many pages per page will be displayed...
$per_page = 20;

//Set the page start variable...
$page_start = ($page_num-1) * $per_page;
 
//Do a number query to see how many results match the category...

$query="SELECT count(*) as num_articles FROM articles_info WHERE status='2' AND username='". addslashes($username) ."' ORDER BY time DESC";
$num_res = mysql_query($query);
$num_object = MYSQL_FETCH_OBJECT($num_res);
$num_of_results = $num_object->num_articles;

// lets try this userlist thingy $USERS



$res = mysql_query ( "SELECT article_id,title,blurb,date,username FROM articles_info WHERE status='2' AND username='". addslashes($username) ."' ORDER BY time DESC limit $page_start,$per_page");
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
            echo "<P>newer |";
     }


     if($page_num > 1){
	     echo "<P><a href=\"$PHP_SELF?username=$username&page_num=$page_back\">newer</a> | ";
     }
  
     if($page_num < $num_of_pages) { 
             echo " <a href=\"$PHP_SELF?username=$username&page_num=$page_forward\">older</a></P>";
     } 

     if($page_num == $num_of_pages) {
             echo " older</P>";
     }

 echo "</P>";

// multiple rows
while ( $individual_row = mysql_fetch_object( $res ) ) {

   echo "<table border=0 cellspacing=0 cellpadding=3><tr><td>\n";
   echo "<P><FONT><a href=\"$url$individual_row->article_id.txt\">\n";
   echo "<B>$individual_row->title</a></B> by\n";

   $name = $individual_row->username;
   $web = $individual_row->web;
      if ($web == "") {
         echo "$name<BR>\n";
      } else {
         echo "<a href='$individual_row->web' target='new'>$individual_row->username</a><br> \n";
      }
   echo "$individual_row->blurb</FONT><br>";
   echo "<font>$individual_row->date ";

$res2 = mysql_query ( "SELECT count(*) as num FROM comments WHERE article_id='$individual_row->article_id' AND status=0");

$d =  mysql_fetch_object($res2);

echo " | $d->num comments";

   echo "</td></tr></table>\n";

}
   echo "<P>";

     if($page_num == 1){
            echo "<P>newer |";
     }


     if($page_num > 1){
	     echo "<P><a href=\"$PHP_SELF?username=$username&page_num=$page_back\">newer</a> | ";
     }
  
     if($page_num < $num_of_pages) { 
             echo " <a href=\"$PHP_SELF?username=$username&page_num=$page_forward\">older</a></P>";
     } 

     if($page_num == $num_of_pages) {
             echo " older</P>";
     }

 echo "</P>";

}

?>




