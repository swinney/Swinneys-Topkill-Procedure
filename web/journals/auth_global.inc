
<?

$hidden_hash_var='your_password_here';

$LOGGED_IN=false;
//clear it out in case someone sets it in the URL or something
unset($LOGGED_IN);


/*

create table user (
user_id int not null auto_increment primary key,
username text,
real_name text,
email text,
password text,
remote_addr text,
confirm_hash text,
is_confirmed int not null default 0
);

*/

function user_isloggedin() {
    global $username,$id_hash,$hidden_hash_var,$LOGGED_IN;
    //have we already run the hash checks? 
    //If so, return the pre-set var
    if (isset($LOGGED_IN)) {
        return $LOGGED_IN;
    }
    if ($username && $id_hash) {
        $hash=md5($username.$hidden_hash_var);
        if ($hash == $id_hash) {
            $LOGGED_IN=true;
            return true;
        } else {
            $LOGGED_IN=false;
            return false;
        }
    } else {
        $LOGGED_IN=false;
        return false;
    }
}

function user_login($username,$password) {
    global $feedback;
    if (!$username || !$password) {
        $feedback .=  ' ERROR - Missing user name or password ';
        return false;
    } else {
        $username=strtolower($username);
        $password=strtolower($password);
        $sql="SELECT * FROM user WHERE username='$username' AND password='". md5($password) ."'";
        $result=db_query($sql);
        if (!$result || db_numrows($result) < 1){
            $feedback .=  ' ERROR - User not found or password incorrect ';
            return false;
        } else {
            if (db_result($result,0,'is_confirmed') == '1') {
                user_set_tokens($username);
                $feedback .=  ' SUCCESS - You Are Now Logged In ';
                return true;
            } else {
                $feedback .=  ' ERROR - You haven\'t Confirmed Your Account Yet ';
                return false;
            }
        }
    }
}

function user_logout() {
    setcookie('username','',(time()+2592000),'/','',0);
    setcookie('id_hash','',(time()+2592000),'/','',0);
}

function user_set_tokens($username_in) {
    global $hidden_hash_var,$username,$id_hash;
    if (!$username_in) {
        $feedback .=  ' ERROR - User Name Missing When Setting Tokens ';
        return false;
    }
    $username=strtolower($username_in);
    $id_hash= md5($username.$hidden_hash_var);

    setcookie('username',$username,(time()+2592000),'/','',0);
    setcookie('id_hash',$id_hash,(time()+2592000),'/','',0);
}

function user_confirm($hash,$email) {
    /*
        Call this function on the user confirmation page,
        which they arrive at when the click the link in the
        account confirmation email
    */

    global $feedback,$hidden_hash_var;

    //verify that they didn't tamper with the email address
    $new_hash=md5($email.$hidden_hash_var);
    if ($new_hash && ($new_hash==$hash)) {
        //find this record in the db
        $sql="SELECT * FROM user WHERE confirm_hash='$hash'";
        $result=db_query($sql);
        if (!$result || db_numrows($result) < 1) {
            $feedback .= ' ERROR - Hash Not Found ';
            return false;
        } else {
            //confirm the email and set account to active
            $feedback .= ' User Account Updated - You Are Now Logged In ';
            user_set_tokens(db_result($result,0,'username'));
            $sql="UPDATE user SET email='$email',is_confirmed='1' WHERE confirm_hash='$hash'";
            $result=db_query($sql);
            return true;
        }
    } else {
        $feedback .= ' HASH INVALID - UPDATE FAILED ';
        return false;
    }
}

function user_change_password ($new_password1,$new_password2,$change_username,$old_password) {
    global $feedback;
    //new passwords present and match?
    if ($new_password1 && ($new_password1==$new_password2)) {
        //is this password long enough?
        if (account_pwvalid($new_password1)) {
            //all vars are present?
            if ($change_username && $old_password) {
                //lower case everything
                $change_username=strtolower($change_username);
                $old_password=strtolower($old_password);
                $new_password1=strtolower($new_password1);

                $sql="UPDATE user SET password='". md5($new_password1). "' ".
                "WHERE username='$change_username' AND password='". md5($old_password). "'";
                $result=db_query($sql);
                if (!$result || db_affected_rows($result) < 1) {
                    $feedback .= ' NOTHING Changed '.db_error();
                    return false;
                } else {
                    $feedback .= ' Password Changed ';
                    return true;
                }
            } else {
                $feedback .= ' Must Provide User Name And Old Password ';
                return false;
            }
        } else {
            $feedback .= ' New Passwords Doesn\'t Meet Criteria ';
            return false;
        }
    } else {
        return false;
        $feedback .= ' New Passwords Must Match ';
    }
}

function user_change_email ($password1,$new_email,$username) {
    global $feedback,$hidden_hash_var;
    if (validate_email($new_email)) {
        $hash=md5($new_email.$hidden_hash_var);
        //change the confirm hash in the db but not the email - 
        //send out a new confirm email with a new hash
        $username=strtolower($username);
        $password1=strtolower($password1);
        $sql="UPDATE user SET confirm_hash='$hash' WHERE username='$username' AND password='". md5($password1) ."'";
        $result=db_query($sql);
        if (!$result || db_affected_rows($result) < 1) {
            $feedback .= ' ERROR - Incorrect User Name Or Password ';
            return false;
        } else {
            $feedback .= ' Confirmation Sent ';
            user_send_confirm_email($new_email,$hash);
            return true;
        }
    } else {
        $feedback .= ' New Email Address Appears Invalid ';
        return false;
    }
}

function user_send_confirm_email($email,$hash) {
    /*
        Used in the initial registration function
        as well as the change email address function
    */

    $message = "Thank You For Registering at Swinney.org".
        "\nSimply follow this link to confirm your registration: ".
        "\n\nhttp://www.swinney.org/journals/account/confirm.phtml?hash=$hash&email=". urlencode($email).
        "\n\nOnce you confirm, you can use the services on Swinney.org.";
    mail ($email,'Swinney.org Registration Confirmation',$message,'From: noreply@swinney.org');
}

function user_register($username,$password1,$password2,$email,$real_name) {
    global $feedback,$hidden_hash_var;
    //all vars present and passwords match?
    if ($username && $password1 && $password1==$password2 && $email && validate_email($email)) {
        //password and name are valid?
        if (account_namevalid($username) && account_pwvalid($password1)) {
            $username=strtolower($username);
            $password1=strtolower($password1);

            //does the name exist in the database?
            $sql="SELECT * FROM user WHERE username='$username'";
            $result=db_query($sql);
            if ($result && db_numrows($result) > 0) {
                $feedback .=  ' ERROR - USER NAME EXISTS ';
                return false;
            } else {
                //create a new hash to insert into the db and the confirmation email
                $hash=md5($email.$hidden_hash_var);
                $sql="INSERT INTO user (username,real_name,password,email,remote_addr,confirm_hash,is_confirmed) ".
                    "VALUES ('$username','$real_name','". md5($password1) ."','$email','$GLOBALS[REMOTE_ADDR]','$hash','0')";
                $result=db_query($sql);
                if (!$result) {
                    $feedback .= ' ERROR - '.db_error();
                    return false;
                } else {
                    //send the confirm email
                    user_send_confirm_email($email,$hash);
                    $feedback .= ' Successfully Registered. You Should Have a Confirmation Email Waiting ';
                    return true;
                }
            }
        } else {
            $feedback .=  ' Account Name or Password Invalid ';
            return false;
        }
    } else {
        $feedback .=  ' ERROR - Must Fill In User Name, Matching Passwords, And Provide Valid Email Address ';
        return false;
    }
}

function user_getid() {
    global $G_USER_RESULT;
    //see if we have already fetched this user from the db, if not, fetch it
    if (!$G_USER_RESULT) {
        $G_USER_RESULT=db_query("SELECT * FROM user WHERE username='" . user_getname() . "'");
    }
    if ($G_USER_RESULT && db_numrows($G_USER_RESULT) > 0) {
        return db_result($G_USER_RESULT,0,'user_id');
    } else {
        return false;
    }
}

function user_getrealname() {
    global $G_USER_RESULT;
    //see if we have already fetched this user from the db, if not, fetch it
    if (!$G_USER_RESULT) {
        $G_USER_RESULT=db_query("SELECT * FROM user WHERE username='" . user_getname() . "'");
    }
    if ($G_USER_RESULT && db_numrows($G_USER_RESULT) > 0) {
        return db_result($G_USER_RESULT,0,'real_name');
    } else {
        return false;
    }
}

function user_getemail() {
    global $G_USER_RESULT;
    //see if we have already fetched this user from the db, if not, fetch it
    if (!$G_USER_RESULT) {
        $G_USER_RESULT=db_query("SELECT * FROM user WHERE username='" . user_getname() . "'");
    }
    if ($G_USER_RESULT && db_numrows($G_USER_RESULT) > 0) {
        return db_result($G_USER_RESULT,0,'email');
    } else {
        return false;
    }
}

function user_getname() {
    if (user_isloggedin()) {
        return $GLOBALS['username'];
    } else {
        //look up the user some day when we need it
        return ' ERROR - Not Logged In ';
    }
}

function account_pwvalid($pw) {
    global $feedback;
    if (strlen($pw) < 6) {
        $feedback .= " Password must be at least 6 characters. ";
        return false;
    }
    return true;
}

function account_namevalid($name) {
    global $feedback;
    // no spaces
    if (strrpos($name,' ') > 0) {
        $feedback .= " There cannot be any spaces in the login name. ";
        return false;
    }

    // must have at least one character
    if (strspn($name,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == 0) {
        $feedback .= "There must be at least one character.";
        return false;
    }

    // must contain all legal characters
    if (strspn($name,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_")
        != strlen($name)) {
        $feedback .= " Illegal character in name. ";
        return false;
    }

    // min and max length
    if (strlen($name) < 5) {
        $feedback .= " Name is too short. It must be at least 5 characters. ";
        return false;
    }
    if (strlen($name) > 15) {
        $feedback .= "Name is too long. It must be less than 15 characters.";
        return false;
    }

    // illegal names
    if (eregi("^((root)|(bin)|(daemon)|(adm)|(lp)|(sync)|(shutdown)|(halt)|(mail)|(news)"
        . "|(uucp)|(operator)|(games)|(mysql)|(httpd)|(nobody)|(dummy)"
        . "|(www)|(cvs)|(shell)|(ftp)|(irc)|(debian)|(ns)|(download))$",$name)) {
        $feedback .= "Name is reserved.";
        return 0;
    }
    if (eregi("^(anoncvs_)",$name)) {
        $feedback .= "Name is reserved for CVS.";
        return false;
    }

    return true;
}

function validate_email ($address) {
    return (ereg('^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+'. '@'. '[-!#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.' . '[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$', $address));
}

?>



