<?
require_once("./global.php");
$query = "UPDATE user SET ip_addr=RAND() WHERE user_id=".addslashes($_SESSION['authenticated_user_id']);
$res = @mysql_query($query);
unset($_SESSION['authenticated_username']);
unset($_SESSION['authenticated_user_id']);
unset($_COOKIE['username']);
session_unset();
session_destroy();
setcookie("authenticated_username",$username,time() - 3600,"/","swinney.org",0);
setcookie("authenticated_user_id",$user_id,time() - 3600,"/","swinney.org",0);

#echo URLBASE;
#die();
header("Location: " . $HTTP_REFERER );
?>









