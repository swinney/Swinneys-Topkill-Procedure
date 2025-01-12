<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$

require_once("./global.php");

if ($article_id) {
  $article_id = explode (".", $article_id);
  $id = $article_id[0];
}
if ($id) {
  $id = explode (".", $id);
  $id = $id[0];
}

@$first .= <<<EOT
<!-- 
here is where we voice our ideas.  raise you hands and ill call on you
in order.
-->

<table cellpadding="0" cellspacing="0" border="0" width="375">
<tr>
<td align="right">
<img src="img/no.gif" alt="" width="1" height="20" border="0"><br>
<a href="submit_comment.php?id=$id" accesskey="s" target="_top" onmouseover="MM11.mouseOver(); window.status='Add a Comment'; return true" onmouseout="MM11.mouseOut(); window.status=' '; return true"><img src="img/addcomment.gif" alt="Add A Comment" width="104" height="23" border="0" name="addcomment1"></a></td></tr>

EOT;

$query = <<<EOT
  SELECT comments.comment_id,
         comments.user_id,
         comments.username,
         comments.comment,
         comments.nature,
         comments.to_user_id,
         comments.language
    FROM comments
   WHERE article_id=$id 
     AND status=0 
EOT;

/*
 * bozo filter is set at login time and contains user_id's to 
 * avoid.
 * - austin, Fri Mar  1, 2002 11:48 AM
 */
if (@$bozo_set) {
  $query .= " AND user_id NOT IN $bozo_set";
}
/*
 * this i presume is the thing to see if it is new.
 * i think bcm wrote this in, but it is not implemented.
 * - austin, Fri Mar  1, 2002 11:48 AM
 */

if (isset($insert_since) && $insert_since) {
  $query .= " AND timestamp > $insert_since";
}
/*
 * this limits the number of characters, part of the noise filter
 * -austin, Fri Mar  1, 2002 11:47 AM
 */
if (@$limit_chars) {
  $query .= " AND chars > $limit_chars";
}

if (@$sess_lang) {
  $lang_str = implode("','",$sess_lang);
  $query .= " AND language IN ('$lang_str') ";
}


$query .= <<<EOT
 ORDER BY comment_id
EOT;

$db = DB::connect($dsn);
if (DB::isError($db)) {
  die($db->getMessage());
}

$res = $db->query($query);
if (DB::isError($res)) {
  die($res->getMessage());
}

$to_users = array();
$html = "";
while ($d = $res->fetchRow(DB_FETCHMODE_OBJECT)) {
  $username = stripslashes($d->username);
  $comment = stripslashes($d->comment);
  $comment_id = $d->comment_id;
  $user_id = $d->user_id;
  $to_user_id = $d->to_user_id;
  $to_users[$user_id]=$username;
  $language = stripslashes($d->language);
  /* build the user link
   */
  if ($user_id!=0) {
  $username = "<a href=\"./info_user.php?uid=$user_id\">$username</a>"; 
  }

  /* LULU MADNESS
   * the things we do for chicks - J.
   * awwwwe yeah - a.
   */
  if ($username == "s5") {
    $username = "<span style=\"background-color:#500000\">$username";
    $comment = "$comment</span>";
  }
  if ($to_user_id != NULL && isset($to_users[$to_user_id]) && $to_user_id != 0 && $to_users[$to_user_id] != NULL) {
    $username .= " to <a href='./info_user.php?uid=" . $to_user_id . "'>" . $to_users[$to_user_id] . "</a>\n";
    $username .= "</b>";
  }

  if (count($sess_lang)>1) {
    $username .=" [$language]";
  }

  if ($username != NULL && $comment != NULL && $comment_id != NULL) { 
    $html .= <<<EOT

<tr>
<td>
<a name="$comment_id"><img src="img/no.gif" alt="" width="1" height="4" border="0"></a><br>
</td>
</tr>

<tr>
<td bgcolor="#999999">
<img src="img/no.gif" alt="" width="1" height="1" border="0"><br>
</td>
</tr>

<tr>
<td>
<img src="img/no.gif" alt="" width="1" height="4" border="0"><br></td>
</tr>

<tr>
<td>
<b>$username :</b> $comment
</td>
</tr>

EOT;
  }
}

// man, I'm so glad this code is here.  I would have been up all
// night trying to figure out how to do this simple thing.  thank you,
// thank you Mr. Swinney. - J.
$last = "";
if ($res->numRows() >= 3) {
  $last .= <<<EOT
  
<tr>
<td>
<img src="img/no.gif" alt="" width="1" height="4" border="0"><br></td>
</tr>

<tr>
<td bgcolor="#999999">
<img src="img/no.gif" alt="" width="1" height="1" border="0"><br></td>
</tr>

<tr>
<td>
<img src="img/no.gif" alt="" width="1" height="4" border="0"><br></td>
</tr>

<tr>
<td align="right">
<a href="submit_comment.php?id=$id" accesskey="s" target="_top" onmouseover="MM12.mouseOver(); window.status='Add a Comment'; return true" onmouseout="MM12.mouseOut(); window.status=' '; return true"><img src="img/addcomment.gif" alt="Add A Comment" width="104" height="23" border="0" name="addcomment2"></a></td>
</tr>
EOT;
}
echo $first;
echo $html;
echo $last;
echo "</table>";
unset ($to_users);
?>









