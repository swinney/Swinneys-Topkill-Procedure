<?
/*
 * $Id$
 */

if ($error_msg) {
  $html .= "<FONT COLOR=\"RED\">$error_msg</FONT>";
  session_unregister("error_msg");
  unset($error_msg);
}
if ($success_msg) {
  $html .= "<FONT COLOR=\"GREEN\">$success_msg</FONT>";
  session_unregister("success_msg");
  unset($success_msg);
}

if (!$uid | $uid==0) {
  $html .= "<P>this user has no id. could be this is an old user reference from back before id's, or it could be you got here the wrong way. try finding the user in this list:</P>";
  $query = "SELECT user_id,username FROM user ORDER BY username";
  $res = mysql_query($query) or die ("<P>Query failed to find users: ". $query);
  while ($d=mysql_fetch_object($res)) {
    $html .=" <a href='$PHP_SELF?uid=$d->user_id'>$d->username</a> | ";
  }
} else {
    $username=get_username($uid);

$query = "SELECT count(articles_info.user_id) FROM articles_info WHERE user_id=$uid AND status IN (2,3)";
$num_articles = $db->getOne($query);
unset($query);
if (DB::isError($db)) {
  die ($db->getMessage());
}
$query = "SELECT count(comments.user_id) FROM comments WHERE user_id=$uid";
$num_comments = $db->getOne($query);
unset($query);
if (DB::isError($db)) {
  die ($db->getMessage());
}

$query = "SELECT distinct(username) from articles_info WHERE user_id=$uid AND username<>'$username' AND username NOT LIKE '% to %'";

$los_nombres = $db->query($query);
unset($query);
if (DB::isError($db)) {
  die ($db->getMessage());
}

$query = "SELECT AVG(nature) FROM comments WHERE user_id=$uid";
$nature_id = $db->getOne($query);
unset($query);
if (DB::isError($db)) {
  die ($db->getMessage());
}

while ($val = $los_nombres->fetchRow()) {
  if (!$names_html) {
    $names_html = " $val[0]";
  } else {
    $names_html .= ", $val[0]";
  }
}

function get_nature() {
  global $nature_id, $db;
  $query = "SELECT nature FROM nature WHERE nature_id=". round($nature_id);
  $nature = $db->getOne($query);
  if (DB::isError($db)) {
    die($db->getMessage());
  }
  return $nature;
}

$nature = get_nature();

include_once("HTML/IT.php");
$tpl = new IntegratedTemplate("./templates");
$tpl->loadTemplateFile("info_user.tpl.html",true,true);
$tpl->setCurrentBlock("info");
$tpl->setVariable("username",$username);
$tpl->setVariable("names_html",$names_html);
$tpl->setVariable("num_articles",$num_articles);
$tpl->setVariable("num_comments",$num_comments);
$tpl->setVariable("nature",$nature);
$tpl->setVariable("uid",$uid);
$tpl->parseCurrentBlock("info");
$tpl->show();

 include("Swinsite/Articles.php");
 $a = new Articles();
 $articles_html = $a->getUserTitles($uid,"id",5);
 echo $articles_html;

}

?>
