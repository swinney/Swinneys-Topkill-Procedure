<?
require_once("Swinsite/Multi.php");


if (!$mid) {
  echo "<P>there was not an id for this multi in the url, and that my friend is a problem.</P>";
} else {
    $m = new Multi();
    $multi = $m->get_multi_fm_id($mid);
    $editor = get_username($multi[user_id]);
    $html = <<<EOT
<P><B>$multi[title]</B></P>
<P><B>edited by $editor</B></P>
<P><B>$multi[abstract]</B></P>

EOT;
}

echo $html;
?>
