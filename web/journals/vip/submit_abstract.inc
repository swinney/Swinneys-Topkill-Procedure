<?
/*
 * $Id$
 */

require_once("Swinsite/Multi.php");
$m = new Multi();
$abstract=$m->get_abstract($multi_id);
$nav = $m->get_nav($multi_id);

$html =<<<EOT
$nav
<P><B>Abstract:</B></P>
<P> $abstract</P>
<FORM NAME="abstract" METHOD=POST ACTION="process_abstract.phtml">
<INPUT TYPE=HIDDEN NAME=multi_id VALUE=$multi_id>
<TEXTAREA NAME=abstract COLS=40 ROWS=10 WRAP=VIRTUAL>$abstract</TEXTAREA><BR>
<INPUT TYPE=SUBMIT NAME=submit VALUE="update">
</FORM>
EOT;
echo $html;
?>


