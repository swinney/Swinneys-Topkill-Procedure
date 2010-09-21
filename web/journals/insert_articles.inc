<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$

require_once("global.inc");
require_once("Swinsite/Language.php");

// count the number of articles so we can calculate the number of
// pages to use
$query = <<<EOT
SELECT count(article_id) AS num_articles
  FROM articles_info
 WHERE status=2 
EOT;
if (count($bozos)) {
  $query .= " AND user_id NOT IN $bozo_set";
}
if ($insert_since) {
  $query .= " AND time > $insert_since";
}
if ($sess_lang) {
  $lang = new Language();
  $query .= " AND language IN ".$lang->parenLang($sess_lang);
}
$query .= " ORDER BY article_id DESC";
$res = $db->query($query);
if (DB::isError($res)) {
  die($res->getMessage($query));
}
$article_info = $res->fetchRow(DB_FETCHMODE_OBJECT);
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
    SELECT article_id, username, user_id, title, blurb, DATE_FORMAT(date,'%Y-%m-%d') as time, num_comments, language
    FROM articles_info
   WHERE status=2 
EOT;
  if ($bozo_set) {
    $query .= " AND user_id NOT IN $bozo_set";
  }
  if ($insert_since) {
    $query .= " AND time > $insert_since ";
  }
  if ($sess_lang) {
    $query .= " AND language IN ".$lang->parenLang($sess_lang);
  }
  $query .= <<<EOT
ORDER BY article_id DESC
   LIMIT $page_start,$per_page
EOT;
  $res = $db->query($query);
  if (DB::isError($res)) {
    die($res->getMessage($query));
  }
  // generate the article listing table
 echo <<<EOT
<table width="300" border="0" cellspacing="0" cellpadding="0">
<tr>
<td>
EOT;

  while ($article = $res->fetchRow(DB_FETCHMODE_OBJECT)) {
    // retrieve the number of comments for the article

    $num_comments = $article->num_comments;

    // generate the summary for the article

    if ($num_comments == 1) {
      $num_comments .= " comment";
    } else {
      $num_comments .= " comments";
    }

    $username = stripslashes($article->username);
    $user_id = stripslashes($article->user_id);
    $blurb = stripslashes($article->blurb);
    if ($blurb) {
      $blurb .= "<br>\n";
    }
    $title= stripslashes($article->title);

    echo <<<EOT
<p>
<a href="article.phtml?id=$article->article_id">
<b>$title</b></a> by <a href="info_user.phtml?uid=$user_id">$username</a><br>
$blurb
<span class="small">$article->time | $num_comments 
EOT;
      if (count($sess_lang) > 1) {
	echo "| [$article->language]";
      }
    echo "</span></p>";
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
