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
$title = $res->fetchRow();


$query = <<<EOT
SELECT multi_articles.article_id,
       articles_info.title 
  FROM multi_articles, 
       articles_info 
 WHERE multi_articles.article_id=articles_info.article_id 
   AND multi_articles.multi_id=$multi_id
EOT;
// Beautiful.


$res = $db->query($query);
if (DB::isError($res)) {
  die($res->getMessage());
}

while ($row = $res->fetchRow()) {
  $html .= <<<EOT
<INPUT TYPE=CHECKBOX NAME="del_id" VALUE=$row[0]>
<A HREF='../article.phtml?id=$row[0]'>$row[1]</A><BR>

EOT;

}

echo <<<EOT
<FORM NAME="multi_articles" ACTION="./process_multi.phtml" METHOD=POST>
<P><B>$title[0]</B></P>
<INPUT TYPE=HIDDEN NAME=multi_id VALUE=$multi_id>
<INPUT TYPE=SUBMIT NAME=submit VALUE="Add">
<INPUT TYPE=TEXT NAME=add_id VALUE="" SIZE=4>
<BR>
$html
<INPUT TYPE=SUBMIT NAME=submit VALUE="Remove">


</FORM>
EOT;
?>