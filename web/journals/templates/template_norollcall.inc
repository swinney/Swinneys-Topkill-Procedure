<? 
#  $Id$

require_once("global.inc");
include "templates/top.inc";
include "templates/swinney.req";
include "templates/norollcall.inc";

include "$into_template";

if (isset($into_template2)) {
  include "$into_template2";
}

include "templates/bottom.req";
include "templates/footer.inc";
?>


