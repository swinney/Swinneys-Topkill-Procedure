<?php
include (INCDIR ."/top.inc");
include (INCDIR ."/swinney.req");
if (@$rollcall==1) {
    include (INCDIR ."/rollcall.inc");
} else {
    include (INCDIR ."/norollcall.inc");
}
include (INCDIR ."/endleft.inc");
include ("$into_template");
if (isset($into_template2)) {
    include "$into_template2";
}
if (basename($_SERVER['PHP_SELF'])=="article.php") {
    /*
     * this is the multi display.
     */
    require_once("Multi.php");
    $m = new Multi();
    $multi=$m->is_multi($id);
    $is_multi_num=$multi[0];
    $multi_id=$multi[1];   
    if ($is_multi_num>0) {
      $multi=$m->get_multi($id,$multi_id,"right");
      /*
       * $multi is html returned.
       */
	$show_multi=$multi;
    }
}
?>
<!-- Right Margin Matter Box -->
</TD>
<td width="33">
<img src="http://swinney.org/dev/journals/img/no.gif" alt="" width="33" height="1" border="0"></td>
<TD WIDTH="150" ALIGN=RIGHT VALIGN=TOP>

<?
if (@$show_multi) {
    echo '<IMG SRC="img/serial.gif">';
    echo $multi;
}
if (isset($a_user_id)){
    @include_once(INCDIR ."/profiles.inc.php");
} else if (preg_match("/search/i", $_SERVER['HTTP_REFERER'])) {
    @include_once(INCDIR ."/adsense_160x600_googlers.inc");
} else {
    @include_once(INCDIR ."/adsense_120x240.inc");
}
?>
</TD>
<?
include (INCDIR ."/bottom.req");
include (INCDIR ."/footer.inc");
?>


