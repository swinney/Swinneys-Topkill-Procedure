<?
/////////////////////////////////////////////
// $Id$
require_once("./global.php");
/////////////////////////////////////////////
// NOTE...
// the level 3 cat_bin in the master categories table
// must have one and only one value.
/*
$ckcat=$db->getOne("SELECT category FROM articles_info WHERE article_id=$id");
if ($ckcat>0) {
    session_register("error_msg");
    $error_msg.="This already has a category";
    $url = URLBASE;
    header("Location: $url");
    exit();
}
*/
if (!isset($cat)) {
  $query="UPDATE articles_info SET category=0 WHERE article_id=$id";
  $res=mysql_query($query) or die (error_page("meh: $query"));
  header("Location: $HTTP_REFERER");
}
if (isset($cat)) {
    $end=array_pop($cat);
    foreach ($cat as $value) {
      $query=$query . $value . " | ";
    }
    $query="UPDATE articles_info SET category=(". $query . $end .") WHERE article_id=$id";
    $res=mysql_query($query) or die (error_page("buh: $query"));
}
header("Location: $HTTP_REFERER");
unset($cat);
?>
