<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$

require_once("global.inc");

// count the number of articles so we can calculate the number of
// pages to use
$query = <<<EOT
SELECT count(*) AS num_articles
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

  // generate the paginator "<< i want to write >>" thinger

  echo "<p>\n";

  if ($page_num == 1){
    echo <<<EOT
<p>
&lt;&lt; <a href="submit_article.phtml">I want to write</a>

EOT;
  }

  if ($page_num > 1){
    echo <<<EOT
<p>
<a href="index.phtml?select=$select&page_num=$page_back">&lt;&lt;</a>
<a href="submit_article.phtml">I want to write</a>;

EOT;
  } 
  
  if ($page_num < $num_of_pages) { 
    echo <<<EOT
<a href="index.phtml?select=$select&page_num=$page_forward">&gt;&gt;</a>
</p>

EOT;
  }

  if ($page_num == $num_of_pages) {
    echo <<<EOT
&gt;&gt;
</p>

EOT;
  }

  echo "</p>\n";

  // retrieve the article data

  $query = <<<EOT
  SELECT *
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
<table width="200" border="0" cellspacing="0" cellpadding="3">
<tr>
<td>
<font size="2">
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

    $num_comments = $comments->num_comments || 0;
    if ($num_comments == 1) {
      $num_comments .= " comment";
    } else {
      $num_comments .= " comments";
    }

    $username = $article->username;
    if ($article->web) {
      $username = <<<EOT
<a href="$article->web" target="_new">$username</a>
EOT;
    }

    $blurb = $article->blurb;
    if ($blurb) {
      $blurb .= "<br>\n";
    }

    echo <<<EOT
<p>
<a href="article.phtml?id=$article->article_id.txt">
<strong>$article->title</strong></a> by $username<br>
$blurb
<font size="1">$article->date</font> | $num_comments
</p>
EOT;
  }

  echo <<<EOT
</td>
</tr>
</table>
EOT;
}

?>
