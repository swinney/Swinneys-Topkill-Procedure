<? 
#  $Id$

include (INCDIR ."/top.inc");
include (INCDIR ."/swinney.req");
if ($rollcall==1) {
  include (INCDIR ."/rollcall.inc");
} else {
  include (INCDIR ."/norollcall.inc");
}
include (INCDIR ."/endleft.inc");

include "$into_template";

if (isset($into_template2)) {
  include "$into_template2";
}


if (basename($PHP_SELF)=="article.phtml") {
/*
 * this is the multi display.
 */
require_once("Swinsite/Multi.php");
$m = new Multi();
$multi=$m->is_multi($id);
$is_multi_num=$multi[0];
$multi_id=$multi[1];

if ($is_multi_num>0) {
  $multi=$m->get_multi($id,$multi_id);
  /*
   * $multi is html returned.
   */
  echo $multi;
}
}
include (INCDIR ."/bottom.req");
include (INCDIR ."/footer.inc");
?>


