<?

/*
 * #########################################################
 * $Id$
 *   vip/global.inc
 *   global setup for the vip section
 */

require_once("../global.inc");

/*
 * if the user has not logged in, then redirect him to the login page!
 */
if (! $authenticated_username) {
  header("Location: " . URLBASE . "/journals/login.phtml");
  exit;
}

?>
