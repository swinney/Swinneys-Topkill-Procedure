<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$


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

  }


  if ($text) {
    $text = stripslashes($text);
  }

  $title = stripslashes($d->title);
  $blurb = stripslashes($d->blurb);
  $category= $d->category; 
  $username = stripslashes($d->username);
  $username = $usernamenourl;
  if ($d->web) {
    $username = <<<EOT
<a href="$d->web">$username</a>
EOT;
  }

$names=get_cat_names($category);
  echo <<<EOT
<table cellpadding="0" cellspacing="0" border="0" width="375">
<tr>
<td colspan="2">
<div class="header"><b>$articletitle</b></div>
 
<div class="text">
<b>$blurb</b></div></td>
</tr>
<tr>
<td>
<P><FONT SIZE=1>$names</font></P>
</td>
</tr>
<tr>
<td colspan="2">
&nbsp;</td>
</tr>

<tr>
<td>
<div class="subheader">
<b>by $username</b></div>
<div class="text">
<b>0$d->date</b></div></td>

<td align="right" nowrap>
<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td align="center" nowrap>
<p class="text">
EOT;

  if ($older_article_id or $newer_article_id) {
  echo "<b><a href=\"userpages.phtml?username=$usernamenourl\">more from this writer</a>:</b><br>";
  }

  if ($older_article_id) {
    echo <<<EOT
<a href="article.phtml?id=$older_article_id.txt">&laquo; earlier</a>
EOT;
    }

  if ($older_article_id and $newer_article_id) {
  echo " - ";
  }
  
  if ($newer_article_id) {
    echo <<<EOT
<a href="article.phtml?id=$newer_article_id.txt">later &raquo;</a>
EOT;
    }

    echo <<<EOT
</p></td>
</tr>
</table></td>
</tr>

<tr>
<td colspan="2">
&nbsp;</td>
</tr>

<tr>
<td colspan="2"> 
$text</td>
</tr>
</table>

EOT;

?>
