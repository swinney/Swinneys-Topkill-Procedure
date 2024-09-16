<?
###################################
# $Id$
# bring the articles
require_once("./global.php");

$title = "Articles by All";
$into_template = "insert_alpha.inc";
# is rollcall.inc displayed?
# 0 for norollcall.inc; 1 for rollcall.inc.
$rollcall=1;
include(INCDIR ."/template.inc");
?>
