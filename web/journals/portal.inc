<?
// protal.inc
// swinney.org, austin swinney, for weeb

include "connect.inc";

if(!$page_num || $page_num < 1) { //No Page Number? Set it to Page 1 then...
        $page_num = 1;
}

//How many pages per page will be displayed...
$per_page = 20;

//Set the page start variable...
$page_start = ($page_num-1) * $per_page;

$res0 = mysql ("$DB","SELECT allow FROM portal where username='weeb'");
$d = mysql_fetch_object($res0);
$allow = $d->allow;

//Do a number query to see how many results match the category...
$num_res = mysql ("$DB", "SELECT count(*) as num_articles FROM pending_articles WHERE status='2' AND username in ($allow) ORDER BY time DESC");
$num_object = MYSQL_FETCH_OBJECT($num_res);
$num_of_results = $num_object->num_articles;

$res = mysql ("$DB", "SELECT * FROM pending_articles WHERE status='2' AND username in ($allow) ORDER BY time DESC limit $page_start,$per_page");
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

   echo "<h1>Last 25 Entries</h1>";
   echo "<P><a href='submit_article.phtml'><strong>I want to write</strong></a></P>";

// multiple rows
while ( $individual_row = mysql_fetch_object( $res ) ) {

   echo "<table border=0 cellspacing=0 cellpadding=3><tr><td>\n";
   echo "<font face='arial' size='2'>\n";
   echo "<a href=\"$url$individual_row->article_id.txt\">\n";
   echo "<B>$individual_row->title</a></B> by\n";

   $name = $individual_row->username;
   $web = $individual_row->web;
      if ($web == "") {
         echo "$name<BR>\n";
      } else {
         echo "<a href='$individual_row->web' target='new'>$individual_row->username</a><br> \n";
      }
   echo "$individual_row->blurb</font><br>";
   echo "<font face=\"arial\" size='1'>$individual_row->date ";

$res2 = mysql("$DB", "SELECT count(*) as num FROM comments WHERE article_id='$individual_row->article_id' AND status=0");

$d =  mysql_fetch_object($res2);

echo " | $d->num comments";

   echo "</td></tr></table>\n";

}
}
 echo "<P>";

     if($page_num == 1){
            print "<PRE><b>$page_num</b> <-- X ";
     }


     if($page_num > 1){
	     print "<PRE><a href=\"index.phtml?select=$select&page_num=$page_back\"><b> $page_num</a></b>  of  ";


     } 

  
     if($page_num < $num_of_pages) { 
             print "<a href=\"index.phtml?select=$select&page_num=$page_forward\"><b> $num_of_pages</b></a></PRE>";
     } 

     if($page_num == $num_of_pages) {
             print "<b>$num_of_pages</b></PRE>";
     }

 echo "</P>";

?>


















