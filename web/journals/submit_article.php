<?
// $Id$

$title = "Submit an Article";
$into_template = "./submit_article.inc";
require_once("./global.php");
$thisurl = "http://swinney.org/journals/submit_article.php";
is_auth($_SESSION['authenticated_username'], $_SESSION['authenticated_user_id'], $thisurl);

include_once(INCDIR ."/template_norollcall.inc");
?>





















