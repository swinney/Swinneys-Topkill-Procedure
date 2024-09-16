<?
// #########################################################
// # $Id$
// # process the submitted registration form, adding a user record to
// # the database, including the ip address so we can track yahoos

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
        // works fine, do nothing
		} else {
		// doesnt work, throw errors
			# set the error code so that we can display it
			if ($error = $resp->error) {
			
				$error_msg = "Your reCaptcha word match was incorrect.";
				$error_redirect = $HTTP_REFERER ;

			}
				
        }
        
} else {

	echo "basically failed.<BR>";
	
}

if ($error_msg) {
  session_register("error_msg");
  header("Location: $error_redirect");
  exit;
}

// make sure a username was submitted
if ($username) {
  if (!preg_match("/^[[:alnum:]_-]{3,}$/",$username)) {
    die("Not OK.  You can only have letters, numbers, _ and - in your username.  No spaces or other junk.  And it needs to be at least three characters.  Sorry Bucko.");
  }
  // check to see if the username is taken
  $query = "SELECT username FROM user WHERE username='$username'";
  $res = mysql_query($query) or
    die(error_page("database error for query $query: " . mysql_error()));
  $matches = mysql_num_rows($res);

  if (! $matches) {
    // make sure the password and a confirmation were submitted
    if ($password && $password2) {
      // make sure the password and confirmation match
      if ($password == $password2) {
        // add the user to the database
        $ip_addr = getenv("REMOTE_ADDR"); 
        $encrypted_password = crypt($password);
        $query =
          "INSERT INTO user (username,password,email,ip_addr) 
           VALUES ('$username','$encrypted_password','$email','$ip_addr')";

        $res = mysql_query($query) or
          die(error_page("database error for query $query: " . mysql_error()));
        // log the user in and store some info in the session
        $user_id = mysql_insert_id();

        $res_ins_setting = mysql_query("INSERT INTO user_settings SET user_id=$user_id");



        include_once("Madmin/User.php");
	$u = new User();
	$u->startPriv($user_id);
        session_register("user_id");

        $_SESSION['authenticated_username'] = $username;
        session_register("authenticated_username");
      } else {
        $error_msg = "Those passwords don't match.  Try again:";
      }
    } else {
      $error_msg = "You must provide a password and confirm it. Try again:";
    }

  } else {
    $rand = dice(1,99);
    $username = "${username}_likes_ham$rand";
    $error_msg = "Username taken. Swinney suggests:";
  }
} else {
  $username = "SucksEggs" . dice(1,99) . dice(1,99);
  $error_msg = "You must provide a username. Swinney suggests:";
}

if ($error_msg) {
  include("./submit_register.php");
} else {
  mail("swinney@gmail.com", "new user $_SESSION['authenticated_username']\n", "new user: $_SESSION['authenticated_username']\nemail: $email");
  header("Location: " . URLBASE);
}
?>
