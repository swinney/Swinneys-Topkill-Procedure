<?php
// -*- Mode: PHP; indent-tabs-mode: nil; =*-
/////////////////////////////////////////////////////////////////
// $Id$
// TODO: _ create a submit box to create a new set
//       _ add a new article to set
//       _ create tables multi_info & multi_articles
//       

if ($submit) {
  $mtitle=addslashes($mtitle);
  $query = "INSERT INTO multi_info SET user_id=$user_id, title='$mtitle'";
  $res = $db->query($query);
  if (DB::isError($res)) {
    die($res->getMessage());
  }
  unset($mtitle);
}
?>


<FORM NAME="add_multi" METHOD="POST" ACTION="<?=$PHP_SELF?>">
<INPUT TYPE=TEXT NAME="mtitle" SIZE=40>
<INPUT TYPE=SUBMIT NAME=submit VALUE="Add Multi">
</FORM>


<?
$query =<<<EOT
SELECT multi_info.multi_id,
       multi_info.title
  FROM multi_info
 WHERE user_id=$authenticated_user_id
ORDER BY title
EOT;
// sweetness.

$res = $db->query($query);
if (DB::isError($res)) {
  die($res->getMessage());
}
while ($row = $res->fetchRow()) {
  $html .= "\n<b>&raquo;</b> <A HREF='submit_multi.phtml?multi_id=$row[0]'>$row[1]</A><BR>";
}

echo $html;

?>  
