<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$


$chunks = explode(".", $id);
$article_id = $chunks[0];

// retrieve the article info

include_once("Swinsite/Articles.php");
$a = new Articles();
$row = $a->getArticle($article_id,$db);

$a_article_id = $row['article_id'];
$a_user_id    = $row['user_id']; 
$a_username   = $row['username'];
$a_web        = $row['web'];
$a_date       = $row['date'];
$a_status     = $row['status'];
$a_title      = $row['title'];
$a_blurb      = $row['blurb'];
$a_category   = $row['category'];
$a_image      = $row['image'];
$a_text       = $row['text'];
unset($row);
if ($a_user_id) {
  // retrieve the id of the author's previous article
  $query = <<<EOT
  SELECT article_id
    FROM articles_info
   WHERE article_id < $a_article_id
    AND user_id=$a_user_id
     AND status=2
ORDER BY article_id DESC
   LIMIT 1
EOT;

  $res = mysql_query($query) or
    die(error_page(mysql_error()));
  if ($row = mysql_fetch_row($res)) {
    $o_article_id = $row[0];
  }

  // retrieve the id of the author's next article

  $query = <<<EOT
  SELECT article_id
    FROM articles_info
   WHERE article_id > $article_id
     AND user_id=$a_user_id
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

  if ($article_row['text']) {
    if ($article_row['image']>0) {
      require_once("Madmin/Image.php");
      $Image = new Image();
      $img_array = $Image->get_img($image,$article_id);
      $article_row['text'] = $Image->show_img($img_array,$article_row['text']);
    }
  }


  include_once("Swinsite/WebAddress.php");
  $webAddress = new WebAddress();
  $web=$webAddress->checkWeb($d->web);

  if ($d->web) {
    $username = <<<EOT
<a href="$a_web">$a_username</a>
EOT;


  }
  if ($a_category) {
      $a_names=get_cat_names($a_category);
  }
  echo <<<EOT
<table cellpadding="0" cellspacing="0" border="0" width="375">
<tr>
<td colspan="2">
<div class="header"><b>$a_title</b></div>
 
<div class="text">
<b>$a_blurb</b></div></td>
</tr>
<tr>
<td>
<P><FONT SIZE=1>$a_names</font></P>
</td>
</tr>
<tr>
<td colspan="2">
&nbsp;</td>
</tr>

<tr>
<td>
<div class="subheader">
<b>by <a href="info_user.phtml?uid=$a_user_id">$a_username</a></b></div>
<div class="text">
<b>$a_date</b></div></td>

<td align="right" nowrap>
<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td align="center" nowrap>
<p class="text">
EOT;

  if ($o_article_id or $newer_article_id) {
  echo "<b><a href=\"userpages.phtml?uid=$a_user_id\">more from this writer</a>:</b><br>";
  }

  if ($o_article_id) {
    echo <<<EOT
<a href="article.phtml?id=$o_article_id">&laquo; earlier</a>
EOT;
    }

  if ($o_article_id and $newer_article_id) {
  echo " - ";
  }
  
  if ($newer_article_id) {
    echo <<<EOT
<a href="article.phtml?id=$newer_article_id">later &raquo;</a>
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
$a_text</td>
</tr>
</table>

EOT;
?>
