<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$
require_once("Swinsite/Articles.php");
$a = new Articles();
$html = $a->get_articles(10);
echo $html;
?>
