<?
/* $Id$
 * add a sucka to bozolist!
 */
require_once("global.php");

if (!$uid) {
  session_register("error_msg");
  $error_msg .= "<P>there is no bozo_id to add!</P>";
  header("Location: $HTTP_REFERER");
  exit();
} else {
  /*
   * get authenticate user id if we dont have it.
   */
  if (!$_SESSION['authenticated_user_id']) {
    session_register("error_msg");
    $error_msg .= "<P>no authenticate user id, setting it.</P>";
    $_SESSION['authenticated_user_id']=get_user_id($_SESSION['authenticated_username']);
    session_register("authenticated_user_id");
  }

  $query = "SELECT count(bozo_id) FROM user_bozo WHERE bozo_id=$uid AND user_id=$_SESSION['authenticated_user_id']";
  $res = mysql_query($query) or die($query);
  $num = mysql_result($res,0);
  if ($num>0) {
      session_register("error_msg");
      $error_msg .= "<P>this person is already a bozo!</P>";
      header("Location: $HTTP_REFERER");
      exit();
  }
  $bozoname=addslashes(get_username($uid));
  if (!$_SESSION['authenticated_user_id']) {
    session_register("error_msg");
    $error_msg .= "<P>you need to be logged in to do this.  no user_id!</P>";
    header("Location: $HTTP_REFERER");
    exit();
  }
  $query ="INSERT INTO user_bozo (user_id,bozo_id,bozoname) VALUES ($_SESSION['authenticated_user_id'],$uid,'$bozoname')";
  $db->query($query);
  if (DB::isError($db)) {
    die($db->getMessage());
  }
  if ($bozo_set) {
    session_unregister("bozo_set");
    unset($bozo_set);
  }
  $bozo_set = get_bozo_set();
  session_register("success_msg");
  $success_msg="This bozo was successfully added!";
  header("Location: $HTTP_REFERER");
  exit();

}
?>
