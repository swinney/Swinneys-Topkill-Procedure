<?php

// common.php

define ("WEBSITE", "SWINNEY.ORG");
define ("NL", "<BR>\n");

function check_email ($str) {
  // Returns 1 if a valid email, 0 if not

  if (ereg ("^.+@.+\\..+$", $str)) {
    return 1;
  } else {
    return 0;
  }

}

?>