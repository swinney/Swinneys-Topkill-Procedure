<?php
// -*- Mode: PHP; indent-tabs-mode: nil; =*-
/////////////////////////////////////////////////////////////////
// $Id$
// should be fed the multi_id

$query = "SELECT title FROM multi_info WHERE multi_id=$multi_id";

$res = $db->query($query);
if (DB::isError($res)) {
  die($res->getMessage());
}
$row = $res->fetchRow();
$title=stripslashes($row[0]);

$query = <<<EOT
SELECT multi_articles.article_id,
       articles_info.title 
  FROM multi_articles, 
       articles_info 
 WHERE multi_articles.article_id=articles_info.article_id 
   AND multi_articles.multi_id=$multi_id
 ORDER BY multi_articles.article_id
EOT;
// Beautiful.


$res = $db->query($query);
if (DB::isError($res)) {
  die($res->getMessage());
}

while ($row = $res->fetchRow()) {
  $html .= <<<EOT
<INPUT TYPE=CHECKBOX NAME="del_id" VALUE=$row[0]>
<A HREF='../article.php?id=$row[0]'>$row[1]</A><BR>
EOT;
}

require_once("Multi.php");
$m = new Multi();
$nav = $m->get_nav($multi_id);
echo <<<EOT
$nav
<FORM NAME="multi_articles" ACTION="./process_multi.php" METHOD=POST>
<P><B>Submit Articles to <i>$title</i></B></P>
<INPUT TYPE=HIDDEN NAME=multi_id VALUE=$multi_id>
<INPUT TYPE=SUBMIT NAME=submit VALUE="Add">article by id:
<INPUT TYPE=TEXT NAME=add_id VALUE="" SIZE=4>
<BR>
$html
<INPUT TYPE=SUBMIT NAME=submit VALUE="Remove">


</FORM>
EOT;
?>
