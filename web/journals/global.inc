<?


#########################################################
# $Id$
# global.inc
# global vars for use in the site
# functions for use in the site


define("DB_HOST", "localhost");
define("DB_USER", "swinney");
define("DB_PASSWD", "mang");
define("DB_NAME", "swinney");


#########################################################
# mangage the cookie system
# syntax for php ccookie is:
# setcookie(name, value, expiration, path, domain, security);
# note: expiration is in seconds, domain must start with period. 
#
# we are calling the cookie "id" and assigning it the 
# value $randval . This particular cookie will expire 
# in four hours (the current time plus 14,400 seconds). 
# The cookie is valid for any page below the document 
# root on the domain swinney.org.

# fire the session up or keep it going if it is already on fire
# session_start();
#  session_destroy();
# step one, assing a random value user id
#if (!isset($id)) {
#	srand((double)microtime()*1000000);
#	$randval = rand();
#	# assign the user a random value cookie
#	setcookie("id",$randval,time()+14400,"/",".swinney.org",0);
#} 

# step two, validate the user
# cookie named valid_user, yes, four hours, / , swinney.org
#setcookie("valid_user","yes",time()+14400,"/",".swinney.org",0);


# to delete the cookie just dont set the username
#setcookie("","",time()+14400,"/",".swinney.org",0);


/*
 * connect to the database. if unsuccessful, display an error message.
 * no reason to make this a function, since nobody would ever have a
 * need to call it!
 */

$conn = @mysql_connect(DB_HOST, DB_USER, DB_PASSWD) or
die(error_page("Connection failed for user '" . DB_USER .
	       "' to database server '" . DB_HOST . "'"));

@mysql_select_db(DB_NAME) or
die(error_page(mysql_error()));

##########################################################
#################  FUNCTION LIST #########################
# here are some functions for the site.  they do different
# things but are mostly here because functions are a
# little easier to deal with than includes because of
# the centralization.  sometimes the files global.inc
# becomes bloated in size, but it has to be pretty big to
# notice.
# austin
##########################################################

/*
 * error_page($msg) - This generates an HTML error page (including
 * head and body tags) displaying the specified error message. The
 * result is useful as an argument for die().
 * ix, Wed Aug 22 11:02:20 PDT 2001
 */

function error_page($msg) {
  include("journals/templates/top.inc");
  $html = <<<EOT
<p>
<b><font color="red">BIG RED FLAG!</font></b>
</p>
<p>
Something is broken. You should <a href="mailto:austin@swinney.org">
email Austin</a> and tell him.
</p>
EOT;

  if ($msg) {
    $html .= <<<EOT
<p>
<b>Error:</b>
<em>$msg</em>
</p>
EOT;
  }

  $html .= <<<EOT

</body>
</html>
EOT;

  return $html;
}

###################################
# dice() - This generates a
# number using a set of dice,
# like 1d6, or 5d2
# austin, Mon Jul 23, 2001  9:50 PM

Function dice( $number, $value )

{       
        
        $total = 0;


        for ( $i = 0 ; $i < $number ; $i++ ) {
                
                srand((double)microtime()*1000000);
                $total += rand(1, $value);

        }
        
        return $total;

}




###################################
# check_web() - evaluates $web
# this thing dont work yet.
# austin, Mon Jul 23, 2001  9:50 PM  

function check_web($web,$username) 

{

	if ($web != "") 

	{

		$username="<a href='".$web."'> ".stripslashes($username)."</a>";
	}


	if ($web == "") 

	{


		echo "$username ";
	}

}

function get_categories($something) {
  // Work out what subjects
  $res = mysql_query ("SELECT MAX(category_id) FROM categories");
  $maxid = mysql_result($res, 0, 0);
  $subject_value = 0;
  for ( $i = 1 ; $i <= $maxid ; $i++ ) {
    $str = "cat".$i;
    if ( $$str == "on" ) {
      $val = pow(2, $i-1);
      $subject_value += $val;
    }
  }

}


?>
