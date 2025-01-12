<? 
// $Id$
if (!$_SESSION['authenticated_username']) {
	$back_to = $URLBASE . $PHP_SELF;
	header("Location: ./login.php");
	
}

require_once("./global.php");

$title = "Add a Comment";
$into_template = "./submit_comment.inc";
include(INCDIR ."/template_norollcall.inc");
?>











