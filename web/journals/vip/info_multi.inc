<?
/* 
 * $Id$
 */

require_once("Swinsite/Multi.php");

$m = new Multi();
$nav = $m->get_nav($multi_id);
$multi = $m->get_multi_fm_id($multi_id);
$editor = get_username($multi[user_id]);
$url_editor = urlencode($editor);

$html .=<<<EOT
$nav
<P><B>$multi[title]</B></P>
<P> - edited by <a href="../userpages.phtml?username=$url_editor">$editor</a></P>
<P>$multi[abstract]</P>
EOT;


echo $html;
?>
