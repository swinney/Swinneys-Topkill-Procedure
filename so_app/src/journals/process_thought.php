<?
#$Id$
require_once("./global.php");

/*
mysql> describe thoughts;
+------------+---------------+------+-----+-------------+----------------+
| Field      | Type          | Null | Key | Default     | Extra          |
+------------+---------------+------+-----+-------------+----------------+
| comment_id | int(11)       |      | PRI | 0           | auto_increment |
| timestamp  | timestamp(14) | YES  |     | NULL        |                |
| username   | varchar(20)   | YES  |     | nappy_sucka |                |
| thought    | text          | YES  |     | NULL        |                |
+------------+---------------+------+-----+-------------+----------------+
*/


  if ( $username == "name" ) {
    echo ("Names don't think, back up and try again.");
    exit;
  }
  if ( $thought == "thought" ) {
    echo ("To thought, you must think.  Back up and try again.");
    exit;
  }
  if ( $username == "" ) {
    echo("There are many names for nothing, you just found one.  Back up and try again.");
    exit;
  }
  if ( $thought == "" ) {
    echo("In nothing, there exists blankness.  Back up and try again.");
    exit;
  }
if (!$_SESSION['authenticated_user_id']) {
  if ($_SESSION['authenticated_username'] && !$_SESSION['authenticated_user_id']) {
    $_SESSION['authenticated_user_id']=get_user_id($_SESSION['authenticated_username']);
  } else {

  $urlbase = URLBASE;
  header("Location: $urlbase/journals/login.php");
  exit();
  }
}
if ($last_lang!=$language) {
    if (!$last_lang) {
      session_register("last_lang",$language);
    }
  $last_lang=$language;
}



$query = "INSERT INTO thoughts SET user_id=".addslashes($_SESSION['authenticated_user_id']).",username='".addslashes($username)."',thought='".addslashes($thought)."',ip_addr='".addslashes($ip_addr)."',language='".addslashes($language)."';";

$res = $db->query($query);
if (DB::isError($res)) {
  die($res->getMessage().$query);
}
header("Location: " . URLBASE);
?>
