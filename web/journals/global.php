<?php
// -*- Mode: PHP; indent-tabs-mode: nil; =*-
////////////////////////////////////////////////////////
// $Id$
$ip_addr = getenv("REMOTE_ADDR");

#$banned_ip = array('130.219.8.253');
// 
// if (in_array($ip_addr,$banned_ip)) {
//   include_once("/home/.carmen/swinney/swinney.org/hacked.html");
//   die();
// }
 
/**
if ($_SESSION['authenticated_username'] && !$_SESSION['authenticated_user_id']) {
    $_SESSION['authenticated_user_id']=get_user_id($_SESSION['authenticated_username']);
}
*/
/*
 * initialize the session. make the session cookie persist for a long,
 * long time. dot his before anything else so that if something dies,
 * we don't get errors about sending headers.
 */
session_set_cookie_params(time()+9999999);
if (session_status() == PHP_SESSION_NONE) {
  session_start();
}
$sess_lang=array("en");

/*
 * if the directory containing global.php also contains
 * local_conf.php, add that directory to the system include path so we
 * can include local_conf.php.
*/

$thisdir = dirname(realpath(__FILE__));

if (file_exists("$thisdir/local_conf.php")) {
    @include_once($thisdir ."/local_conf.php");
}


$thisurl = "http://" . $_SERVER['HTTP_HOST'] . $_SERVER['SCRIPT_NAME'];
if ($_SERVER['QUERY_STRING']) {
  $thisurl .= "?" . $_SERVER['QUERY_STRING'];
}

/*
 * migrating from article_id to id
 */
#if ($article_id) {
#  $id=$article_id;
#}

/*
 * set default configuration values.
 *
 * XXX: would like to set these before including the local config
 * file, but define("foo") seems to cause an error if define("foo")
 * has already been executed. and we want to keep the
 * if(!defined("foo")) statements out of the local config file, to
 * keep it simple.
 */

if (!defined("SITE_NAME")) {
    define("SITE_NAME", "Swinney.org");
}

if (!defined("URLBASE")) {
    define("URLBASE", "http://localhost"); // no trailing slash!
}

if (!defined("DIRBASE")) {
    define("DIRBASE", "/app");
}

if (!defined("INCDIR")) {
    define("INCDIR", "/app/journals/templates");
}

if (!defined("IMGBASE")) {
    define("IMGBASE", "/journals/images");
}

if (!defined("IMGURL")) {
    define("IMGURL", URLBASE . "/journals/images");
}

if (!defined("CSS_URL")) {
    define("CSS_URL", URLBASE . "/journals/main.css");
}

if (!defined("DB_HOST")) {
    define("DB_HOST", "localhost");
}

if (!defined("DB_USER")) {
    define("DB_USER", "swinney");
}

if (!defined("DB_PASSWD")) {
    define("DB_PASSWD", "xxxxxxx");
}

if (!defined("DB_NAME")) {
    define("DB_NAME", "swinney");
}

/*
 * put all include files other than global.php in this library
 * directory, which should be located outside the site's document
 * root.
 */

if (defined("LIBDIR")) {
    use_lib(LIBDIR);
} else {
	echo "libdir broken";
}

/*
 * poor man's object directory: set up a global array in which we can
 * store named resources
 */
$_SESSION['SWINSITE'] = array();

/*
 * connect to the database. if unsuccessful, display an error message.
 * no reason to make this a function, since nobody would ever have a
 * need to call it!
 */

include_once("DB/DB.php");
include_once("HTML/Table.php");

$dsn = array(
             'phptype' => "mysqli",
             'hostspec' => DB_HOST,
             'database' => DB_NAME,
             'username' => DB_USER,
             'password' => DB_PASSWD
             );
$auth_dsn = array(
             'phptype' => "DB",
             'hostspec' => DB_HOST,
             'database' => DB_NAME,
             'username' => DB_USER,
             'password' => DB_PASSWD
             );

$_SESSION['dsn'] = $dsn;
$options = array(
	'debug'	=> 2
);
$db = DB::connect($_SESSION['dsn'], $options);
if (PEAR::isError($db)) {
    die (error_page("can't connect to the database: " . $db->getMessage()));
}

/*
 * cache the database handle in the object directory
 */

if (!$sess_lang) {
  $lang_cond=array();
  $langz = explode(", ",$HTTP_ACCEPT_LANGUAGE);
  if ($langz) {
    foreach ($langz as $lang) {
      $lang = substr($lang,0,2);
      if (!in_array($lang,$lang_cond)) {
	$lang_cond[]="$lang";
      }
    }
  } else {
    $lang_cond[0]='en';
  }
  session_register("sess_lang");
  $sess_lang = $lang_cond;
  unset($langz);
  unset($lang);
  unset($lang_cond);
}

##########################################################
#################  FUNCTION LIST #########################
# here are some functions for the site.  they do different
# things but are mostly here because functions are a
# little easier to deal with than includes because of
# the centralization.  sometimes the files global.php
# becomes bloated in size, but it has to be pretty big to
# notice.
# austin
##########################################################
////////////////////////////////////
// PRETTY_STATUS($int) display pretty 
////////////////////////////////////
function pretty_status($int) {
    switch ($int) {
        case 0 :
            $int = "<FONT COLOR='#CCCCCC'>unset</FONT>";
            break;  
        case 1 :
            $int = "<FONT COLOR='black'>pending</FONT>";
            break;  
        case 2 :
            $int = "<FONT COLOR='black'>actived</FONT>";
 break;  
        case 3 :
            $int = "<FONT COLOR='black'>archived</FONT>";
            break;  
 case 4 :
            $int = "<FONT COLOR='black'>trashed</FONT>";
            break;  
    }
    return $int;
}

/*
 * use_lib($dir) - add $dir to the system include_path
 * ix, Fri Feb  1 21:45:30 PST 2002
 */

function use_lib($dir) {
    $include_path = ini_get("include_path");
    if (isset($include_path)) {
        $include_path = join(":", array($include_path, $dir));
        if (! ini_set("include_path", $include_path)) {
            die("can't set include_path [$include_path]");
        }
    }
}

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
<title>Error</title>
</head>
<body>

EOT;

    if (PEAR::isError($msg)) {
	$msg .= $msg->message . ": [" . $msg->userinfo . "]";
    }

#    if (PEAR::isError($e)) {
#	$msg .= $e->message . ": [" . $e->userinfo . "]";
# }

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

Function dice( $number, $value ) {       
    $total = 0;
    for ($i=0;$i<$number;$i++) {
        srand((double)microtime()*1000000);
        $total += rand(1, $value);
        }        
    return $total;
}

##################################
# bin($dec) function for converting
# decimals to binary.
function bin($pos,$dec){
  $bin = sprintf("%". $pos."b", $dec);
  $bin = ereg_replace(" ","0",$bin);
  $bin = chunk_split($bin,4); 
  return $bin;
}


####################################
# get_cat_names() get the cat names

function get_cat_names($category) {
  global $db;
  $db->setFetchMode(DB_FETCHMODE_OBJECT);
  if ($category) {
      $query="SELECT name FROM categories WHERE level1&$category";
      $res=$db->query($query);
      if (DB::isError($res)) {
        die($res->getMessage(). " $query");
      }
      $num=$res->numRows();
      $i=0;
      $names="";
      while ( $d =& $res->fetchRow() ) {
          $names=$names . $d->name;
          $i++;
          if ($i>0 && $i<$num) {
              $names=$names . " / ";
          }
      }
      if ($names=="") {
          $names="none";
      }
      return $names;
   }
}
/////////////////////////////////////////
// GET_IMG() - retireve the image names
/////////////////////////////////////////
function get_img($id) {
$query="SELECT image FROM articles_info WHERE article_id=$id";
$res=mysql_query($query) or die (error_page($query));
  if (mysql_num_rows($res)>0) {
     $images=mysql_result($res,0,0);

//
// show images if they exist
//
    $img_name=array();
    for ($i = 1; $i <= $images ; $i++) {
        $noext = $id."_".$i;
        if (file_exists(IMGBASE ."/$noext.jpg")) {
            $imgfile = "$noext.jpg";
        } else if (file_exists(IMGBASE ."/$noext.jpeg")) {
            $imgfile = "$noext.jpeg";
        } else if (file_exists(IMGBASE ."/$noext.pjpeg")) {
            $imgfile = "$noext.pjpeg";
        } else if (file_exists(IMGBASE ."/$noext.gif")) {
            $imgfile = "$noext.gif";
        } else if (file_exists(IMGBASE ."/$noext.png")) {
            $imgfile = "$noext.png";
        } else {
            echo "unrecognized file upload: ". IMGBASE ."/$noext.*<BR>";   
 }
        if ($imgfile) {
 array_push($img_name,$imgfile);
        }
    }
    return $img_name;
  }
}
///////////////////////////////////////
// SHOW_IMG()
///////////////////////////////////////
function show_img($img,$text) {
    preg_match_all("/(%%img)(\d{1,2})(%{2})/",$text,$out,PREG_PATTERN_ORDER);
    for ($i=0;isset($out[0][$i]);$i++) {
        $usekey=$out[2][$i]-1;
        $replace= IMGBASE . "/" . $img[$usekey];
        $text=ereg_replace($out[0][$i],$replace,$text);
    }
    return $text;
}

///////////////////////////
// get_username(user_id)
///////////////////////////

function get_username($user_id) {
  global $db; // Use the existing $db handler

  // Prepare the query with a placeholder for the user_id
  $query = "SELECT username FROM user WHERE user_id = ?";

  // Execute the query with the user_id parameter
  $res = $db->query($query, [$user_id]);

  // Check if the query execution was successful
  if (PEAR::isError($res)) {
      die('Query failed: ' . $res->getMessage());
  }

  // Fetch the first result
  $row = $res->fetchRow(DB_FETCHMODE_ASSOC);

  // Return the username or null if not found
  return $row ? $row['username'] : null;
}

function get_user_id($username) {
  $query="SELECT user_id FROM user WHERE username='$username'";
  $res=mysql_query($query);
  if (mysql_num_rows($res)>0) {
    $user_id=mysql_result($res,0,0);
  } else {
    $user_id=0;
  }
  return $user_id;
}
////////////////////////////
// check authorization
///////////////////////////
/**
if (!$_SESSION['authenticated_username'] || !$_SESSION['authenticated_user_id']) {

  $ip_addr = getenv ("REMOTE_ADDR"); // get the ip number of the user
  if ($ip_addr != "" && $ip_addr != "127.0.0.1") {  
      $query = "SELECT user_id,username FROM user WHERE ip_addr='$ip_addr' AND ip_addr != '' ORDER BY last DESC LIMIT 1";
      $res = mysql_query($query) or die("Failed to generate autologin: $query");
      if ($res) {
	$d=mysql_fetch_object($res);
           $_SESSION['authenticated_user_id'] = stripslashes($d->user_id);
           $_SESSION['authenticated_username'] = stripslashes($d->username);
      }
  } else {
    $query = "SELECT ip_addr FROM user WHERE user_id=$_SESSION['authenticated_user_id']";
    $res = mysql_query($query);
    if ($res) {
      $test_ip = getenv ("REMOTE_ADDR");
      if (stripslashes(mysql_result($res,0,0)) != $test_ip) {
	unset($_SESSION['authenticated_user_id']);
	unset($_SESSION['authenticated_username']);
      }
    }
  }
}
  */
function is_auth($thisurl) {
    if ($_SESSION['authenticated_username'] && $_SESSION['authenticated_user_id']) {
        return OK;
        exit; // Note: exit after return is unnecessary as return already ends the function.
    }
    if (!$_SESSION['authenticated_username'] && $_SESSION['authenticated_user_id']) {
        unset($_SESSION['authenticated_user_id']);
        exit; 
    }
    if (!$_SESSION['authenticated_user_id'] && $_SESSION['authenticated_username']) {
        unset($_SESSION['authenticated_username']);
        exit; 
    }
    if (!$_SESSION['authenticated_user_id'] && !$_SESSION['authenticated_username']) {
        header("Location: " . URLBASE . "/journals/login.php?back_to=$thisurl");
        exit;
    }
}

///////////////////////////
// get_rollcall() - 
// the roll call list
///////////////////////////

function get_rollcall() {
  $minus=time();
  $minus=$minus-7776000;
  $query = <<<EOT
SELECT DISTINCT(username), 
       COUNT(username) AS number, 
       status, 
       time
  FROM articles_info
 WHERE status=2
EOT;

// Apply the bozo filter
//
  if ($bozos_set) {
    $query .= " AND user_id NOT IN $bozo_set";
  }
  $query .= " GROUP BY username";

  $res = mysql_query($query) or
    die(error_page(mysql_error()));

  while ($row = mysql_fetch_row ($res)) {

##########################################
# this cannot be called $username
# without interfearing with the url's
# $username.  so it will be called $user.
# austin, Thu Jul 12, 2001  1:40 PM

    $name=$row[0];
    $urlname=urlencode($row[0]);
    $number=$row[1];
    $status=$row[2];
    $time=$row[3];

    if ($number >= 5) {
      $rollcall .= "<a href='userpages.php?username=$urlname'>$name</a> ($number)<br>\n";
    }
  }
  return $rollcall;
}


//////////////////////////////////////
// get_comments($id,$db) - 
// selects out all the comments into
// a big ass multi-dimensional array
// then delivers the good through a for
// loop and formats it in html using
// PEARS Table.php formatting library.
// austin, Tue Feb  5, 2002  4:41 PM
//////////////////////////////////////

function get_comments($id,$db) {
  $query = <<<EOT
  SELECT username,comment_id,comment
    FROM comments
   WHERE article_id=$id
     AND status=0 
EOT;

  if (count($bozos)) {
    $query .= " AND user_id NOT IN $bozo_set";
  }
  if ($insert_since) {
    $query .= " AND timestamp > $insert_since";
  }

  $query .= <<<EOT
ORDER BY comment_id
EOT;

  $comments = $db->getAll($query);
  $table = new HTML_TABLE("cellpadding=0 cellspacing=0 border=0 width=375");

   // $contentABC are formatting elements.
   // they go in addRow("$content","$attr","$type")

   // contentA is specific to the loop, see below.
   $attrA='';
   $contentB=array('<img src="img/no.gif" alt="" width="1" height="1" border="0"><br>');
   $attrB='bgcolor="#999999"';
   $contentC=array('<img src="img/no.gif" alt="" width="1" height="4" border="0"><br>');
   $attrC='';
   // contentD is specific to the loop, see below.
   $attrD='';

  foreach ($comments as $key=>$val) {
    /**
     * strip the slashes
     */
    $val[0]=stripslashes($val[0]); // is username
    $val[2]=stripslashes($val[2]); // is text
    /**
     * here is the loop specific content.
     */
 $contentA=array("<a name='$val[1]'><img src='img/no.gif' alt='' width=1 height=4 border=0></a><br>");
    $contentD=array("<P><B>$val[0]:</B> $val[2]</P>");

    $table->addRow($contentA,$attrA,"TD");
    $table->addRow($contentB,$attrB,"TD");
    $table->addRow($contentC,$attrC,"TD");
    $table->addRow($contentD,$attrD,"TD");
  }
  return $table->toHTML();
} // end function get_comments()

/*
 * get cat none () - display link to categorize
 */

function get_cat_none($id) {
    $url=URLBASE;
    $none=<<<EOT
&raquo; <a href="$url/journals/submit_category.php?id=$id">categorize this</a>
EOT;
    return $none;
}

function get_bozo_set() {
  // Use the session superglobal directly
  if (isset($_SESSION['authenticated_user_id'])) {
      // Initialize $bozo_set to ensure it's available within this scope
      $bozo_set = null;
      
      // Use a prepared statement or at least properly escape your SQL to avoid SQL injection
      $user_id = intval($_SESSION['authenticated_user_id']); // Make sure the user ID is safe to use directly
      $query = "SELECT bozo_id FROM user_bozo WHERE user_id=$user_id";
      $res = mysql_query($query) or die(mysql_error());

      // Construct the bozo set string
      while ($d = mysql_fetch_object($res)) {
          if (!$bozo_set) {
              $bozo_set = "($d->bozo_id";
          } else {
              $bozo_set .= ",$d->bozo_id";
          }
      }

      // Close the set with a parenthesis if it was set
      if ($bozo_set) {
          $bozo_set .= ")";
      }

      return $bozo_set;
  }

  // Optional: return null or another indicator if the user is not authenticated
  return null;
}


// if (ERROR_REP==1) {
//     if (!preg_match("/process/i",$_SERVER['PHP_SELF'])) { 
//         var_dump($sess_lang);
//     }
// }

?>
