<? 
#########################################
# $Id$
# bring the user's articles.
require_once("./global.php");

$into_template="insert_user_articles.inc";
// $title="Articles by $username";
# is rollcall.inc displayed?
# 0 for norollcall.inc; 1 for rollcall.inc.
$rollcall=1;
include(INCDIR ."/template.inc");
?>


