<?php
// -*- Mode: PHP; indent-tabs-mode: nil; =*-
/////////////////////////////////////////////////////////////////
// $Id$
// TODO: _ create a submit box to create a new set
//       _ add a new article to set
//       _ create tables multi_info & multi_articles
//       

if ($mtitle) {
  $title=addslashes($title);
  $query = "UPDATE multi_info SET title='$mtitle' WHERE multi_id=$multi_id";
  $res = $db->query($query);
  if (DB::isError($res)) {
    die($res->getMessage());
  }
} else {
  $query = "SELECT title FROM multi_info WHERE multi_id=$multi_id";
  $mtitle = $db->getOne($query);
}

require_once("Multi.php");
$m = new Multi();
$nav = $m->get_nav($multi_id);

$html =<<<EOT
$nav
<FORM NAME="add_multi" METHOD="POST" ACTION="$PHP_SELF">
<INPUT TYPE=HIDDEN NAME=multi_id VALUE=$multi_id>
<INPUT TYPE=TEXT NAME="mtitle" VALUE="$mtitle" SIZE=40>
<INPUT TYPE=SUBMIT NAME=submit VALUE="Add Multi">
</FORM>
EOT;
echo $html;
?>


