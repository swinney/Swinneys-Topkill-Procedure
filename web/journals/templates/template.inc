<? 
#  $Id$

require_once("global.inc");
include "templates/top.inc";
include "templates/swinney.req";
if ($rollcall==1) {
  include "templates/rollcall.inc";
} else {
  include "templates/norollcall.inc";
}
include "templates/endleft.inc";
include "$into_template";

if (isset($into_template2)) {
  include "$into_template2";
}

include "templates/bottom.req";
include "templates/footer.inc";
?>


