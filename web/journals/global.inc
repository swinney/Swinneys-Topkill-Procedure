<?


#########################################################
# $Id$
# global.inc
# global vars for use in the site
# functions for use in the site


define("WWW_ROOT", "http://swinney.org/dev/journals");
define("TITLE", "swinney.org");


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
session_start();

# step one, assing a random value user id
if (!isset($id)) {
	srand((double)microtime()*1000000);
	$randval = rand();
	# assign the user a random value cookie
	setcookie("id",$randval,time()+14400,"/",".swinney.org",0);
} 

# step two, validate the user
# cookie named valid_user, yes, four hours, / , swinney.org
setcookie("valid_user","yes",time()+14400,"/",".swinney.org",0);

# to delete the cookie just dont set the username
# setcookie("valid_user","",time()+14400,"/",".swinney.org",0);

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

###################################
# conn() - database connection,
# returns error if db is down.
# austin, Mon Jul 23, 2001  9:50 PM

Function conn()

{       
        
        $conn=@mysql_connect("localhost", "swinney", "XXXXXXXX");
        @mysql_select_db("swindev");
 
        if ( $conn == false)

        {       
                
                echo "<font size=6 color=red><b>We are moving to Saturn5.com<br>";
                echo "<br>thanks for your patience.</b></font></body></html>";
                exit;

        }


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