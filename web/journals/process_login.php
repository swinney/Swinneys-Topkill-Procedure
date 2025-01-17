<?
// $Id$

require_once("./global.php");

require_once('../recap/recaptchalib.php');

// Get a key from http://recaptcha.net/api/getkey
$publickey = "6Lc2XwkAAAAAAGEm9BljcoLg8us0scyuB0WmTnd_";
$privatekey = "6Lc2XwkAAAAAAJbXJrjQAK-hYqtFBAE4FW37wlPD";


# was there a reCAPTCHA response?
if ($_POST["recaptcha_response_field"]) {
        $resp = recaptcha_check_answer ($privatekey,$_SERVER["REMOTE_ADDR"],
                                        $_POST["recaptcha_challenge_field"],
                                        $_POST["recaptcha_response_field"]);

        if ($resp->is_valid) {
			// ok
		} else {
                # set the error code so that we can display it
			if ($error = $resp->error) {
			
				$error_msg = "Your reCaptcha word match was incorrect.";
				$error_redirect = "login.php";

			}
				
        }
        
}

if ($error_msg) {
  session_register("error_msg");
  header("Location: $error_redirect");
  exit;
}


if ($username && $password) {
  // pull user info from the database
  $query = <<<EOT
SELECT user_id, username, password
  FROM user
 WHERE username='$username'
EOT;

  $auth_db = DB::connect($auth_dsn);
  if (DB::isError($auth_db)) {
    die ($auth_db->getMessage());
  }
  $res = $auth_db->query($query);
  $user = $res->fetchRow(DB_FETCHMODE_OBJECT);
  if (DB::isError($user)) {
    die ($user->getMessage());
  }

  // make sure the user exists
  if ($user) {
    // verify the submitted credentials
    if (crypt($password, $user->password) == $user->password) {
    } else {
      $error_msg = "Incorrect password.  Please try again:";
      $error_redirect = "login.php";
    }
  } else {
    // username does not exist in the database
    $error_msg =
      "$username is unregistered. <a href=\"submit_register.php?username=$username\">Register it now</a>, or try again:";
    $error_redirect = "login.php";
  }
} else {
  $error_msg = "Enter both username and password to log in:";
  $error_redirect = "login.php";
}

if ($error_msg) {
  session_register("error_msg");
  header("Location: $error_redirect");
  exit;
}

// save some info in the session so other pages can access it later
// in the session


$_SESSION['authenticated_user_id'] = $user->user_id;
setcookie("authenticated_user_id",$_SESSION['authenticated_user_id'],time()+1296000,"/","swinney.org",0);
$_SESSION['auth']['user_id']=$_SESSION['authenticated_user_id'];

$_SESSION['authenticated_username'] = $user->username;
setcookie("authenticated_username",$username,time()+1296000,"/","swinney.org",0);
$_SESSION['auth']['username']=$_SESSION['authenticated_username'];

$ip_addr = getenv("REMOTE_ADDR"); 

$query = "UPDATE user SET ip_addr='$ip_addr',last=NOW() WHERE user_id=$_SESSION['authenticated_user_id']";

@mysql_query($query);


$bozo_set=get_bozo_set();

#$query = "SELECT language FROM user WHERE user_id=$_SESSION['authenticated_user_id']";

#$lang = $db->getOne($query);

#if (DB::isError($lang)) {
#  die($lang->getMessage().$query);
#}

#session_register("sess_lang");
#$sess_lang = explode(",",$lang);


// $back_to is the location where the user originally clicked the "log
// in" link
if (!$back_to || $back_to=="http://www.swinney.org/journals/login.php") {
    $back_to=URLBASE;
}
$auth_db->disconnect();
header ("Location: $back_to");
?>

