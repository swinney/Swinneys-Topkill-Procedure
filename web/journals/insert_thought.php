<?

$query = "SELECT comment_id,user_id,username,thought FROM thoughts WHERE status=0 ";
// Initialize $bozo_set to ensure it's defined

if (isset($bozo_set) && $bozo_set != "") {
    if ($bozo_set == "()") {
        $bozo_set = get_bozo_set(); // Assuming get_bozo_set() returns a valid set or null
    }
    $query .= " AND user_id NOT IN $bozo_set ";
}

if (isset($insert_since)) {
  $query .= " timestamp > $insert_since ";
}

if (isset($sess_lang)) {
  require_once("Language.php");
  $lang = new Language();
  $query .= " AND language IN ".$lang->parenLang($sess_lang);
}

$query .=" ORDER BY comment_id DESC LIMIT 5";
if (ERROR_REP==1) {
  echo $query;
}
// $res = mysql_query ($query) or die($query);
$db->setFetchMode(DB_FETCHMODE_OBJECT);

$res=$db->query($query);
if (DB::isError($res)) {
  die($res->getMessage());
}

// multiple rows 
// while ( $d = mysql_fetch_object( $res ) ) {
  while ( $d =& $res->fetchRow() ) {
    

  // move it to strip slashes
  $username=$d->username;
  $thought=$d->thought;
  $user_id=$d->user_id;
  // echo and strip
  $username=stripslashes($username);
  $thought=stripslashes($thought);

  $ext = substr($thought,-3);

  if (preg_match("/src/i","$thought") || $ext == "jpg"||$ext == "JPG"||$ext == "gif"||$ext == "png" || $ext=="bmp") {
  #	echo"<tr>\n<td align=\"right\" valign=\"top\"
  #	class=\"thoughts\" nowrap>\n</td>\n\n<td valign=\"top\"
  #	class=\"thoughts\" nowrap></td>\n\n<td valign=\"top\"
  #	class=\"thoughts\">\n( IMAGE )</td>\n</tr>\n\n";
    echo"<tr>\n<td align=\"right\" valign=\"top\" class=\"thoughts\" nowrap>\n</td>\n\n<td valign=\"top\" class=\"thoughts\" nowrap></td>\n\n<td valign=\"top\" class=\"thoughts\">\n<img src='$thought'></td>\n</tr>\n\n";
  } else {
        
    echo "<tr>\n<td align=\"right\" valign=\"top\" class=\"thoughts\" nowrap>\n<a href='./journals/info_user.php?uid=$user_id'>$username</a></td>\n\n<td valign=\"top\" class=\"thoughts\" nowrap>\n&nbsp;.o0O</td>\n\n<td valign=\"top\" class=\"thoughts\">\n($thought)</td>\n</tr>\n\n";
  }
}
?>






