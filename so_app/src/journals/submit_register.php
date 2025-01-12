<?
// $Id$
require_once("./global.php");

// doesn't make sense to display the register page for users who are
// already logged in
if (isset($_SESSION['authenticated_username'])) {
  header("Location: " . $HTTP_REFERER);
}

$title = "Registration is open";
$into_template = "./submit_register.inc";
include("./templates/template_norollcall.inc");
?>