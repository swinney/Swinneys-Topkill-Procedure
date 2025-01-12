<?
/*
 * $Id$
 */
$error_msg = "";
$success_msg = "";
$uid = 0;
$location = array();
$names_html = "";
$nature = "";
$edit = "";
$articles_html = "";

if ($error_msg) {
  $html .= "<FONT COLOR=\"RED\">$error_msg</FONT>";
  session_unregister("error_msg");
  unset($error_msg);
}
if ($success_msg) {
  $html .= "<FONT COLOR=\"GREEN\">$success_msg</FONT>";
  session_unregister("success_msg");
  unset($success_msg);
}
$uid = $_GET['uid'];
if (!$uid | $uid==0) {
  $html .= "<P>this user has no id. could be this is an old user reference from back before id's, or it could be you got here the wrong way. try finding the user in this list:</P>";
  $query = "SELECT user_id,username FROM user ORDER BY username";
  // Create a database connection
  $db = DB::connect($_SESSION['dsn'], $options);
  if (PEAR::isError($db)) {
    die('Database connection failed: ' . $db->getMessage());
  }
  $res = $db->query($query) or die ("<P>Query failed to find users: ". $query);
  if (ERROR_REP==1) {
    echo $query . "<BR><BR>";
  }
  while ($d = $res->fetchRow(DB_FETCHMODE_OBJECT)) {
    $user_id = stripslashes($d->user_id);
    $html .= " <a href='". $_SERVER['PHP_SELF'] ."?uid=$d->user_id'>$d->username</a> | ";
  }
} else {
  $query = "SELECT user.username,user.email,user.language,user.city,user.state,user.country,country_codes.country_name,IFNULL(user_settings.lj_user,'') as lj_user, IFNULL(user_settings.cn_user,'') as cn_user, IFNULL(user_settings.fr_user,'') as fr_user, IFNULL(user_settings.fl_user,'') as fl_user FROM user,user_settings,country_codes WHERE user.user_id=".addslashes($uid)." AND user.country=country_codes.two_char AND user.user_id=user_settings.user_id";

  if (ERROR_REP==1) {
    echo $query . "<BR><BR>";
  }
  $res = $db->query($query);
  if (DB::isError($db)) {
    die ($db->getMessage());
  }

  $d = $res->fetchRow(DB_FETCHMODE_OBJECT);
  $this_username = stripslashes($d->username);
  $this_email = stripslashes($d->email);
  $this_language = stripslashes($d->language);
  $this_city = stripslashes($d->city);
  $this_state = stripslashes($d->state);
  $this_country = stripslashes($d->country);
  $lj_user = stripslashes($d->lj_user);
  $cn_user = stripslashes($d->cn_user);
  $fr_user = stripslashes($d->fr_user);
  $fl_user = stripslashes($d->fl_user);
  if ($this_city) {
    $location[0] = "$this_city";
  }
  if ($this_state) {
    $location[1] ="$this_state";
  }
  if ($this_country) {
    $location[2] ="$this_country";
  }

  $location = implode(", ", $location);
  $this_country_flag = "./images/f0-".strtolower($this_country).".gif";
  if (is_file("$this_country_flag")) {
    $location .=" <img alt='Flag Of Country' src='$this_country_flag'>";
  }
  $query = "SELECT count(articles_info.user_id) FROM articles_info WHERE user_id=$uid AND status IN (2,3)";

  if (ERROR_REP==1) {
    echo $query . "<BR><BR>";
  }
  $num_articles = $db->getOne($query);
  unset($query);
  if (DB::isError($db)) {
    die ($db->getMessage());
  }
  // if you dont have an index on comments.user_id, 
  // it is going to take a FOREVER
  $query = "SELECT count(comments.user_id) FROM comments WHERE user_id=$uid";
  if (ERROR_REP==1) {
    echo $query . "<BR><BR>";
  }
  $num_comments = $db->getOne($query);
  unset($query);
  if (DB::isError($db)) {
    die ($db->getMessage());
  }
  
  $query = "SELECT distinct(username) from articles_info WHERE user_id=$uid AND username<>'$this_username' AND username NOT LIKE '% to %'";
  if (ERROR_REP==1) {
    echo $query . "<BR><BR>";
  }
  $los_nombres = $db->query($query);
  if (!$los_nombres) {
    $los_nombres="none";
  }

  unset($query);
  if (DB::isError($db)) {
    die ($db->getMessage());
  }
  

  $query = "SELECT count(user_id) from thoughts where user_id=".addslashes($uid);

  if (ERROR_REP==1) {
    echo $query . "<BR><BR>";
  }
  $num_thoughts = $db->getOne($query);
  if (!$num_thoughts) {
    $num_thoughts="none";
  }

  unset($query);
  if (DB::isError($db)) {
    die ($db->getMessage());
  }
  


  $query = "SELECT AVG(nature) FROM comments WHERE user_id=$uid";
  if (ERROR_REP==1) {
    echo $query . "<BR><BR>";
  }
  $nature_id = $db->getOne($query);
  unset($query);
  if (DB::isError($db)) {
    die ($db->getMessage());
  }
  
  while ($val = $los_nombres->fetchRow()) {
    if (!$names_html) {
      $names_html = " $val[0]";
    } else {
      $names_html .= ", $val[0]";
    }
  }
  
  function get_nature($db,$nature_id) {
    if ($nature_id<1) {
      $nature_id=1;
    }
    $query = "SELECT nature FROM nature WHERE nature_id=". round($nature_id);
    $nature = $db->getOne($query);
    if (DB::isError($db)) {
      die($db->getMessage());
    }
    return $nature;
  }
  
  if ($nature_id != 0) {
  $nature = get_nature($db,$nature_id);
  } else {
    $nature="expressionless";
  }
  if ($_SESSION['authenticated_user_id']==$uid) {
    $edit="[<a href='./vip/submit_location.php?uid=$uid'>edit</a>]";
  }
  require_once 'HTML/Template/IT.php';
  $tpl = new HTML_Template_IT("./templates");
  $tpl->loadTemplateFile("info_user.tpl.html",true,true);
  
  $tpl->setCurrentBlock("info");
  $tpl->setVariable("username",$this_username);
  $tpl->setVariable("names_html",$names_html);
  $tpl->setVariable("num_articles",$num_articles);
  $tpl->setVariable("num_comments",$num_comments);
  $tpl->setVariable("nature",$nature);
  $tpl->setVariable("num_thoughts",$num_thoughts);
  $tpl->setVariable("uid",$uid);
  $tpl->setVariable("location",$location);
  $tpl->setVariable("edit",$edit);
  $tpl->setVariable("lj_user",$lj_user);
  $tpl->setVariable("cn_user",$cn_user);
  $tpl->setVariable("fr_user",$fr_user);
  $tpl->setVariable("fl_user",$fl_user);

  $tpl->parseCurrentBlock("info");
  $tpl->show("info");
  
  include("Articles.php");
  $a = new Articles($db);
  $articles_html = $a->getUserTitles($uid,"id",5);
  echo $articles_html;
  echo "<P><B>5 most recent comments<BR>\n<A HREF='usercomments.php?uid=$uid'>&laquo; more</a></B></P>\n";
  $query = "select CONCAT('As ',comments.username,' on ',articles_info.username,'\'s <b>',articles_info.title,'</b>') as text,comments.article_id, comments.comment_id from comments,articles_info where comments.article_id=articles_info.article_id AND comments.user_id=$uid order by comment_id DESC limit 5";
  $res = $db->query($query);
  if (DB::isError($res)) {
    die($res->getMessage());
  }
  
  while ($row = $res->fetchRow(DB_FETCHMODE_ASSOC)) {
    $tpl->setCurrentBlock("comments");
    $tpl->setVariable("text",stripslashes($row['text']));
    $tpl->setVariable("comment_article_id",stripslashes($row['article_id']));
    $tpl->setVariable("comment_id",stripslashes($row['comment_id']));
    $tpl->parseCurrentBlock("comments");
  }
  $tpl->show("comments");
}
?>
