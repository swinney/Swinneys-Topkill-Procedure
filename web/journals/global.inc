<?

#########################################################
# $Id$
# global.inc
# global vars for use in the site
# functions for use in the site

define("URLBASE", "/dev"); // no trailing slash!
define("DIRBASE", "/u/swinney/htdocs/dev/swinney.org");
define("CSS_URL", URLBASE . "/journals/main.css");
define("DB_HOST", "localhost");
define("DB_USER", "swinney");
define("DB_PASSWD", "mauf4rais");
define("DB_NAME", "swinney");

/*
 * initialize the session
 * 
 * XXX: make the session cookie persist until the user clicks logout
 * (and therefore causes a session_destroy().
 */
session_cache_limiter('nocache');
session_start();

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
  $css_url = CSS_URL;
  $html = <<<EOT
<html>
<head>
<title>swinney.org: error!</title>
<link rel="stylesheet" type="text/css" href="$css_url">
</head>
</body>
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
