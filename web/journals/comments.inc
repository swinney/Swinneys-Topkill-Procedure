<?
// $Id$

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
$query = <<<EOT
  SELECT count(*) AS num_articles
    FROM comments
   WHERE status=0
EOT;
if (count($bozos)) {
  $query .= " AND username NOT IN $bozo_set ";
}
if ($insert_since) {
  $query .= " AND timestamp > $insert_since ";
}
$query .= <<<EOT
 ORDER BY timestamp DESC
EOT;

$res = mysql_query($query) or
  die(error_page(mysql_error(). " with query: $query"));
$row = mysql_fetch_row($res);

if (!$row) {
  echo <<<EOT
<p>
No comments!

</p>
EOT;
} else {
  $num_of_results = $row[0];

  // Find out how many pages there are going to be
  // number of results returned divided by the number per page displayed
  $num_of_pages = $num_of_results/$per_page; 

  // Find out if the num_of_pages was a decimal.. Can't have 2.1 pages...
  $remainders = $num_of_results%$per_page; 

  //If is was a decimal, turn it into an integer and add 1 to it...
  if($remainders != 0){
    $num_of_pages = intval($num_of_pages) + 1;
  }

  $page_back = $page_num - 1;
  $page_forward = $page_num + 1;

  // pull the current page's comments
  $query = <<<EOT
  SELECT username, comment, comment_id, comment, article_id
    FROM comments
   WHERE status=0
EOT;
  if (count($bozos)) {
    $query .= " AND username NOT IN $bozo_set";
  }
  if ($insert_since) {
    $query .= " AND timestamp > $insert_since";
  }
  $query .= <<<EOT
 ORDER BY timestamp DESC limit $page_start,$per_page
EOT;
  $res = mysql_query($query) or
    die(error_page(mysql_error()));

  // write paginator
  $url = "article.phtml?id=$d->article_id";

  if($page_num == 1){
    print "<P>newer |";
  }

  if($page_num > 1){
    print "<P><a href=\"$return?&page_num=$page_back\">newer</a> |";
  } 

  if($page_num < $num_of_pages) { 
    print " <a href=\"$return?page_num=$page_forward\">older</a>";
  } 

  if($page_num == $num_of_pages) {
    print "older</P>";
  }

  // write comments
  while ($d = mysql_fetch_object($res)) {
    $comment_id = $d->comment_id;
    $username   = stripslashes($d->username);
    $comment    = stripslashes($d->comment);
    $article_id = $d->article_id;

    $query = <<<EOT
  SELECT username, title
    FROM articles_info
   WHERE article_id=$article_id
EOT;
    $res2 = mysql_query($query);
    $row = mysql_fetch_row($res2);
    echo "\n<hr>";
    echo <<<EOT
<P>$username on 
"<a href='article.phtml?id=$article_id.txt#$comment_id'>$row[1]</A>" 
by <a href='userpages.phtml?username=$row[0]'>$row[0]</a></P>
<P>$comment</P>
EOT;
  }

  if($page_num == 1){
    print "<P>newer |";
  }

  if($page_num > 1){
    print "<P><a href=\"$return?&page_num=$page_back\">newer</a> |";
  } 

  if($page_num < $num_of_pages) { 
    print " <a href=\"$return?page_num=$page_forward\">older</a>";
  } 

  if($page_num == $num_of_pages) {
    print "older</P>";
  }
}
?>







