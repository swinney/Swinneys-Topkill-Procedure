<?php
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$
require_once("./journals/global.php");


$title = "this is it.";


include(INCDIR ."/top.inc");
#include("./newfeature.inc");
#include("./index_pimp.html");

if (!empty($success_msg)) {
  unset($_SERVER['success_msg']);
  // don't bother printing the success message
}
?>

<table width="100%" cellpadding="20" cellspacing="0" border="0">
<tr>
<td bgcolor="#666666" align="center">
<?php
#include_once("./personals/personal.html");
?>
</td>
<td bgcolor="#666666" align="center">

<table cellpadding="2" cellspacing="0" border="0">
<?php
if ($error_msg = error_get_last()) {
  echo "<FONT COLOR=\"red\"><B>". var_dump($error_msg) ."</B></FONT>";
  unset($error_msg);
}
// include i thought it

// Check if the session variable is set and not empty
if (!empty($_SESSION['authenticated_username'])) {
  // Check if the file exists before including it
  $file_path = "./journals/submit_thought.php";
  if (file_exists($file_path)) {
      include($file_path);
  } else {
      // Handle the error if the file does not exist
      echo "Error: The required file does not exist.";
  }
}
?>

<tr>
<td bgcolor="#666666">
<table cellpadding="0" cellspacing="0" border="0" width="450">
<?php
// include the thoughts
include "journals/insert_thought.php"; 
?>

</table></td>
</tr>
</table></td>
</tr>
</table><table width="100%" cellpadding="0" cellspacing="0" border="0">
<tr>
<td bgcolor="#666666" align="center">

<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td bgcolor="#666666" valign="bottom" align="right" width="174" nowrap><img src="journals/img/no.gif" alt="" width="5" height="1" border="0"><a href="journals/index.php" accesskey="j" target="_top" onmouseover="MM2.mouseOver(); window.status='Articles'; return true" onmouseout="MM2.mouseOut(); window.status=' '; return true"><img src="journals/img/articles.gif" alt="Articles" width="62" height="24" border="0" name="articles"></a><a href="journals/comments.php" accesskey="c" target="_top" onmouseover="MM3.mouseOver(); window.status='Comments'; return true" onmouseout="MM3.mouseOut(); window.status=' '; return true"><img src="journals/img/comments.gif" alt="Comments" width="73" height="24" border="0" name="comments"></a><a href="journals/faq.php" accesskey="f" target="_top" onmouseover="MM4.mouseOver(); window.status='FAQ'; return true" onmouseout="MM4.mouseOut(); window.status=' '; return true"><img src="journals/img/faq.gif" alt="FAQ" width="34" height="24" border="0" name="faq"></a></td>

<td bgcolor="#666666" valign="bottom" align="center" width="284">
<img src="journals/img/swinneylgtop.gif" alt="swinney.org" width="284" height="37" border="0"></td>

<td bgcolor="#666666" valign="bottom" align="right" width="177" nowrap>

<?
if ($_SESSION['authenticated_username'] ?? false) {
} else {
  echo '<a href="journals/submit_article.php" accesskey="e" target="_top" onmouseover="MM5.mouseOver(); window.status=\'Submit\'; return true" onmouseout="MM5.mouseOut(); window.status=\' \'; return true"><img src="journals/img/submit.gif" alt="Submit" width="53" height="24" border="0" name="submit"></a><a href="journals/submit_register.php" target="_top" onmouseover="MM6.mouseOver(); window.status=\'Register\'; return true" onmouseout="MM6.mouseOut(); window.status=\' \'; return true"><img src="journals/img/register.gif" alt="" width="63" height="24" border="0" name="register"></a><a href="journals/login.php" target="_top" onmouseover="MM7.mouseOver(); window.status=\'Log In\'; return true" onmouseout="MM7.mouseOut(); window.status=\' \'; return true"><img src="journals/img/login.gif" alt="" width="48" height="24" border="0" name="login"><img src="journals/img/no.gif" alt="" width="5" height="1" border="0"></td>';
}

if ($_SESSION['authenticated_username']?? false) {
  echo '<a href="journals/submit_article.php" accesskey="e" target="_top" onmouseover="MM5.mouseOver(); window.status=\'Submit\'; return true" onmouseout="MM5.mouseOut(); window.status=\' \'; return true"><img src="journals/img/submit.gif" alt="Submit" width="53" height="24" border="0" name="submit"></a><a href="journals/vip/index.php" target="_top" onmouseover="MM8.mouseOver(); window.status=\'Settings\'; return true" onmouseout="MM8.mouseOut(); window.status=\' \'; return true"><img src="journals/img/settings.gif" alt="" width="62" height="24" border="0" name="settings"></a><a href="journals/process_logout.php" target="_top" onmouseover="MM9.mouseOver(); window.status=\'Log Out\'; return true" onmouseout="MM9.mouseOut(); window.status=\' \'; return true"><img src="journals/img/logout.gif" alt="" width="57" height="24" border="0" name="logout"></a><img src="journals/img/no.gif" alt="" width="5" height="1" border="0"></td>';
}
?>

</tr>
</table>
</td>
</tr>
<tr>
<td align="center">
<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td width="164">
</td>
<td align="center" valign="top" width="284">
<img src="journals/img/swinneylgbottom.gif" alt="" width="284" height="13" border="0"></td>
<td align="right" valign="top" width="172">
<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td>
<?
if ($_SESSION['authenticated_username'] ?? false ) {
echo <<<EOT
<form name="searchform" action="journals/search.php" method="get">
<input type="text" size="12" name="find" value="
EOT;

if ($find) { 
	echo "$find"; 
}

echo <<<EOT
"></td>
<td>&nbsp;<script type="text/javascript" language="JavaScript">
//<!--
document.write('<a href="javascript:document.searchform.submit()" target="_top" onmouseover="MM10.mouseOver(); window.status=\'Search\'; return true" onmouseout="MM10.mouseOut(); window.status=\' \'; return true"><img src="journals/img/search.gif" alt="Search" name="search" width="54" height="23" border="0"></a>');
//-->
</script>
<noscript><input type=submit value="Search"></noscript>
</form>
EOT;
}
?>
</td>
</tr>
</table></td>
</tr>
</table></td>
</tr>
</table>

<table cellpadding="0" cellspacing="0" border="0" width="100%">
<tr>
<td>
<img src="journals/img/no.gif" alt="" width="1" height="10" border="0"></td>
</tr>

<tr>
<td align="center">

<table width="600">
<tr>

<td align="right" valign="top">
<img src="journals/img/now.gif" alt="Now:" width="66" height="20" border="0"></td>

<td valign="top">

<?
include_once("Articles.php");
$a = new Articles($db);
$articles = $a->getTitles("id",5,$db);
echo $articles;

?>
</td>
<td colspan="3">
<img src="journals/img/no.gif" alt="" width="58" height="25" border="0">
</td>
<td align="right" valign="top">
<img src="journals/img/before.gif" alt="Before:" width="87" height="24" border="0"></td>

<td valign="top" colspan="2">
<?
$articles = $a->getTitles("rand", 5, $db);
echo $articles;
?>

</td>
</tr>
</table></td>
</tr>
</table>
<?
include "journals/templates/footer.inc";
?>

