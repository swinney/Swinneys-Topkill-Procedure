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
 ORDER BY comment_id DESC
EOT;

$res = mysql_query($query) or
  die(error_page(mysql_error()));
$row = mysql_fetch_row($res);

if (!$row) {
  echo <<<EOT
<span class="subheader"><b>No comments have been made.</b></span>

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
 ORDER BY comment_id DESC limit $page_start,$per_page
EOT;
  $res = mysql_query($query) or
    die(error_page(mysql_error()));

  // write paginator
  $url = "article.phtml?id=$d->article_id";
  
// let's cut a nice little page header into here - J. 
  /** TODO: make this nav crap a function in global.inc
echo <<<EOT

<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td nowrap>
<span class="subheader"><b>All &raquo;</b></span></td>

<td>&nbsp;&nbsp;&nbsp;</td>

<td align="left">
<span class="subheader"><a href="index.phtml">Articles</a> by <a href="alpha.phtml">Alpha</a> | <b>Comments</b>
EOT;

if ($page_num < $num_of_pages or $page_num > 1) {

echo <<<EOT
</span></td>
</tr>

<tr>
<td colspan="2">&nbsp;</td>
<td align="left">
<span class="text">

EOT;

  if ($page_num < $num_of_pages) { 
    echo <<<EOT
<a href="$return?page_num=$page_forward">&laquo; earlier comments</a>

EOT;
  }  

  if ($page_num < $num_of_pages and $page_num > 1) { 
    echo ' - ';
    }
  
  if ($page_num > 1){
    echo <<<EOT
<a href="$return?page_num=$page_back">later comments &raquo;</a>
EOT;
  }
    
}

echo <<<EOT

</span>
</td>
</tr>
</table>

<br>

<table cellpadding="0" cellspacing="0" border="0" width="375">
<tr>
<td>
<img src="img/no.gif" alt="" width="1" height="4" border="0"></a><br></td>
</tr>

<tr>
<td bgcolor="#999999">
<img src="img/no.gif" alt="" width="1" height="1" border="0"><br></td>
</tr>

<tr>
<td>
<img src="img/no.gif" alt="" width="1" height="4" border="0"><br></td>
</tr>

EOT;


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
    echo <<<EOT
<tr>
<td><a name="$comment_id"></a>
<b><a href='article.phtml?id=$article_id.txt#$comment_id'>$username</a></b> on
"<a href="article.phtml?id=$article_id.txt">$row[1]</a>" 
by <a href='userpages.phtml?username=$row[0]'>$row[0]</a>:<br>

$comment

</td>
</tr>

<tr>
<td>
<img src="img/no.gif" alt="" width="1" height="4" border="0"></a><br></td>
</tr>

<tr>
<td bgcolor="#999999">
<img src="img/no.gif" alt="" width="1" height="1" border="0"><br></td>
</tr>

<tr>
<td>
<img src="img/no.gif" alt="" width="1" height="4" border="0"><br></td>
</tr>

EOT;
}


echo <<<EOT

</table>

EOT;

if ($page_num < $num_of_pages or $page_num > 1) {

echo <<<EOT

<p>

EOT;

  if ($page_num < $num_of_pages) { 
    echo <<<EOT
<a href="$return?page_num=$page_forward">&lt;&lt; earlier comments</a>

EOT;
  }  

  if ($page_num < $num_of_pages and $page_num > 1) { 
    echo ' - ';
    }
  
   if ($page_num > 1){
    echo <<<EOT
<a href="$return?&page_num=$page_back">later comments &gt;&gt;</a>

EOT;
  }
  
  }
  }
?>
