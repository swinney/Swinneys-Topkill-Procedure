<?
// $Id$
require_once("./global.php");


// Doesn't make sense to display the login page for users who are already logged in
if (isset($_SESSION['authenticated_username'])) {
    $authenticated_username = htmlspecialchars($_SESSION['authenticated_username'], ENT_QUOTES, 'UTF-8');
    
    $error_msg .= <<<EOT
ERROR: Your authenticated username: $authenticated_username<BR>
seems to be set already. <a href="mailto:bugs@swinney.org">bugs@swinney.org</a>.
<BR><BR>
EOT;
}
$title = "Log In";
$into_template = "./login.inc";
include(INCDIR ."/template_norollcall.inc");
?>
