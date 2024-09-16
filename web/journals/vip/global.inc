<?

/*
 * #########################################################
 * $Id$
 *   vip/global.php
 *   global setup for the vip section
 */

require_once("../global.php");

/*
 * if the user has not logged in, then redirect him to the login page!
 */
if (! $_SESSION['authenticated_username']) {
  header("Location: " . URLBASE . "/journals/login.php");
  exit;
}

?>
