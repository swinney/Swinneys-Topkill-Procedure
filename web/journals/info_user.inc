<?
/*
 * $Id$
 */

echo $bozo_set;

if ($error_msg) {
  echo "<FONT COLOR=\"RED\">$error_msg</FONT>";
  session_unregister("error_msg");
  unset($error_msg);
}
if ($success_msg) {
  echo "<FONT COLOR=\"GREEN\">$success_msg</FONT>";
  session_unregister("success_msg");
  unset($success_msg);
}

$username=get_username($uid);

$query = "SELECT count(articles_info.user_id) FROM articles_info WHERE user_id=$uid";
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

$query = "SELECT distinct(username) from articles_info WHERE user_id=$uid AND username<>'$username'";
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

$html .= <<<EOT
<TABLE>
  <TR>
    <TD><P>user: </TD>
    <TD><B>$username</B></TD>
  </TR>
  <TR>
    <TD><P>alias: </TD>
    <TD><B>$names_html</B></TD>
  </TR>
  <TR>
    <TD>number of articles: </TD>
    <TD><B>$num_articles</B></TD>
  </TR>
  <TR>
    <TD>number of comments: </TD>
    <TD><B>$num_comments</B></TD>
  </TR>
  <TR>
    <TD>average nature: </TD>
    <TD><B>$nature</B></TD>
  </TR>
</TABLE>
EOT;

$html .= <<<EOT
<FORM NAME="bozo" METHOD="POST" ACTION="process_bozo_id.phtml">
<INPUT TYPE=HIDDEN NAME=uid VALUE=$uid>
<INPUT TYPE=SUBMIT NAME=add_bozo_id VALUE="add to bozo list">
</FORM>
EOT;


echo $html;
?>
