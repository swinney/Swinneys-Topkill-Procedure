<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$

require_once("global.inc");

// count the number of articles so we can calculate the number of
// pages to use
$query = <<<EOT
SELECT count(article_id) AS num_articles
  FROM articles_info
 WHERE status=2 
EOT;
if (count($bozos)) {
  $query .= " AND username NOT IN $bozo_set";
}
if ($insert_since) {
  $query .= " AND time > $insert_since";
}
$query .= " ORDER BY time DESC";

$res = mysql_query($query) or
  die(error_page(mysql_error()));

$article_info = mysql_fetch_object($res);
$num_articles = $article_info ? $article_info->num_articles : 0;

if ($num_articles) {

  // default to page 1
  if (!$page_num || $page_num < 1) {
    $page_num = 1;
  }

  // how many articles to display per page
  $per_page = 20;

  // index of the first article on the page
  $page_start = ($page_num-1) * $per_page;
 
  // total number of pages
  $num_of_pages = $num_articles/$per_page; 
 
  // if the number of pages is a fraction, round it up
  $remainders = $num_articles%$per_page; 
  if ($remainders != 0){
    $num_of_pages = intval($num_of_pages) + 1;
  }

  // previous page number
  $page_back = $page_num - 1;

  // next page number
  $page_forward = $page_num + 1;


echo <<<EOT

<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td nowrap>
<span class="subheader"><b>All &raquo;</b></span></td>

<td>&nbsp;&nbsp;&nbsp;</td>

<td align="left">
<span class="subheader"><b>Articles</b> by <a href="./alpha.phtml">Alpha</a> | <a href="comments.phtml">Comments</a>

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
<a href="index.phtml?page_num=$page_forward">&laquo; earlier articles</a>

EOT;
  }  

  if ($page_num < $num_of_pages and $page_num > 1) { 
    echo ' - ';
    }
  
  if ($page_num > 1){
    echo <<<EOT
<a href="index.phtml?page_num=$page_back">later articles &raquo;</a>
EOT;
  }
  
}

echo <<<EOT

</span>
</td>
</tr>
</table>

<br>

EOT;


  // retrieve the article data

  $query = <<<EOT
     SELECT article_id, username, title, blurb, date
    FROM articles_info
   WHERE status=2 
EOT;
  if (count($bozos)) {
    $query .= " AND username NOT IN $bozo_set";
  }
  if ($insert_since) {
    $query .= " AND time > $insert_since ";
  }
  $query .= <<<EOT
ORDER BY time DESC
   LIMIT $page_start,$per_page
EOT;

  $res = mysql_query ($query) or
    die(error_page(mysql_error()));

  // generate the article listing table

  echo <<<EOT
<table width="300" border="0" cellspacing="0" cellpadding="0">
<tr>
<td>
EOT;

  while ($article = mysql_fetch_object($res)) {
    // retrieve the number of comments for the article

    $subquery = <<<EOT
  SELECT count(*) AS num_comments
    FROM comments
   WHERE article_id=$article->article_id
     AND status=0
EOT;
    if (count($bozos)) {
      $subquery .= " AND username NOT IN $bozo_set";
    }

    $subres = mysql_query($subquery) or
      die(error_page(mysql_error()));
    $comments = mysql_fetch_object($subres);

    // generate the summary for the article

    $num_comments = $comments->num_comments;
    if ($num_comments == 1) {
      $num_comments .= " comment";
    } else {
      $num_comments .= " comments";
    }

    $username = $article->username;

    $blurb = $article->blurb;
    if ($blurb) {
      $blurb .= "<br>\n";
    }

    echo <<<EOT
<p>
<a href="article.phtml?id=$article->article_id.txt">
<b>$article->title</b></a> by <a href="userpages.phtml?username=$username">$username</a><br>
$blurb
<span class="small">$article->date | $num_comments</span>
</p>
EOT;
  }


  echo <<<EOT
</td>
</tr>
</table>
<p>

EOT;
}

  // generate the paginator 

  if ($page_num < $num_of_pages) { 
    echo <<<EOT
<a href="index.phtml?select=$select&page_num=$page_forward">&laquo; earlier articles</a>

EOT;
  }  
  
    if ($page_num < $num_of_pages and $page_num > 1) { 
    echo ' - ';
    }
  
   if ($page_num > 1){
    echo <<<EOT
<a href="index.phtml?select=$select&page_num=$page_back">later articles &raquo;</a>

EOT;
  }
  echo "</p>\n";



?>
