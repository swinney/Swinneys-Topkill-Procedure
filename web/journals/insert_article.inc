<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$

require_once("global.inc");

$chunks = explode(".", $id);
$article_id = $chunks[0];

// retrieve the article info

$query = <<<EOT
  SELECT *
    FROM articles_info
   WHERE article_id=$article_id
EOT;

$res = mysql_query($query) or
  die(error_page(mysql_error()));

if ($d = mysql_fetch_object($res)) {
  // retrieve the article text
  $query = <<<EOT
  SELECT text
    FROM articles_text
   WHERE article_id=$article_id
EOT;

  $res = mysql_query($query) or
    die(error_page(mysql_error()));

  $text = mysql_result($res, 0);

  // retrieve the id of the author's previous article

  $query = <<<EOT
  SELECT article_id
    FROM articles_info
   WHERE article_id < $article_id
     AND username='$d->username'
     AND status=2
ORDER BY article_id DESC
   LIMIT 1
EOT;

  $res = mysql_query($query) or
    die(error_page(mysql_error()));
  if ($row = mysql_fetch_row($res)) {
    $older_article_id = $row[0];
  }

  // retrieve the id of the author's next article

  $query = <<<EOT
  SELECT article_id
    FROM articles_info
   WHERE article_id > $article_id
     AND username='$d->username'
     AND status=2
ORDER BY article_id ASC
   LIMIT 1
EOT;

  $res = mysql_query($query) or
    die(error_page(mysql_error()));
  if ($row = mysql_fetch_row($res)) {
    $newer_article_id = $row[0];
  }

  // generate the paginator

  echo <<<EOT
<p>
EOT;

  if ($newer_article_id) {
    echo <<<EOT
<a href="article.phtml?id=$newer_article_id.txt">newer</a> 
EOT;
  } else {
    echo " newer";
  }

  echo " | ";

  if ($older_article_id) {
    echo <<<EOT
<a href="article.phtml?id=$older_article_id.txt"> older</a>
EOT;
  } else {
    echo " older";
  }

  echo <<<EOT
</tt>
</p>
EOT;

  // generate the article display
  if ($text) {
    $text = stripslashes($text);
  }

  $title = stripslashes($d->title);
  $blurb = stripslashes($d->blurb);

  $username = stripslashes($d->username);
  if ($d->web) {
    $username = <<<EOT
<a href="$d->web" target="_new">$username</a>
EOT;
  }

  echo <<<EOT
<h2>$title</h2>
<h4>$blurb</h4>
<h4>by $username<br>
$d->date</h4>
$text
EOT;
}

?>
