<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$

$db = DB::connect($_SESSION['dsn'], $options);
if (PEAR::isError($db)) {
    die (error_page("can't connect to the database: " . $db->getMessage()));
}

$chunks = explode(".", $id);
$article_id = $chunks[0];

// retrieve the article info

if ($a_user_id) {
  // retrieve the id of the authors previous article

}

  include_once("WebAddress.php");
  $webAddress = new WebAddress();
  @$web=$webAddress->checkWeb($webAddress->web);

  if (@$d->web) {
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
<b>by <a href="info_user.php?uid=$a_user_id">$a_username</a></b></div>
<div class="text">
<b>$a_date</b></div></td>

<td align="right" nowrap>
<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td align="center" nowrap>
<p class="text">
EOT;

  if ($p_article_id or @$newer_article_id) {
  echo "<b><a href=\"userpages.php?uid=$a_user_id\">more from this writer</a>:</b><br>";
  }

  if ($p_article_id) {
    echo <<<EOT
<a href="article.php?id=$p_article_id">&laquo; earlier</a>
EOT;
    }

  if ($p_article_id && $n_article_id) {
  echo " - ";
  }
  
  if ($n_article_id) {
    echo <<<EOT
<a href="article.php?id=$n_article_id">later &raquo;</a>
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
