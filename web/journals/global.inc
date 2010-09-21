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
if ($authenticated_username && !$authenticated_user_id) {
    $authenticated_user_id=get_user_id($authenticated_username);
}
*/
/*
 * initialize the session. make the session cookie persist for a long,
 * long time. dot his before anything else so that if something dies,
 * we don't get errors about sending headers.
 */
session_start();
session_set_cookie_params(time()+9999999);

$sess_lang=array("en");

/*
 * if the directory containing global.inc also contains
 * local_conf.php, add that directory to the system include path so we
 * can include local_conf.php.
*/

$thisdir = dirname(realpath(__FILE__));

if (file_exists("$thisdir/local_conf.php")) {
    @include_once($thisdir ."/local_conf.php");
}


$thisurl = "http://". $HTTP_HOST . $SCRIPT_NAME;
if ($QUERY_STRING) {
    $thisurl .= "?". $QUERY_STRING;
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
    define("URLBASE", "http://swinney.org"); // no trailing slash!
}

if (!defined("DIRBASE")) {
    define("DIRBASE", "/sky/www/swinney.org/html");
}

if (!defined("INCDIR")) {
    define("INCDIR", "/sky/www/swinney.org/html/journals/templates");
}

if (!defined("IMGBASE")) {
    define("IMGBASE", "/sky/www/swinney.org/html/dev/journals/images");
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
 * put all include files other than global.inc in this library
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
$SWINSITE = array();

/*
 * connect to the database. if unsuccessful, display an error message.
 * no reason to make this a function, since nobody would ever have a
 * need to call it!
 */

include_once("DB.php");
include_once("HTML/Table.php");

$dsn = array(
             'phptype' => "mysql",
             'hostspec' => DB_HOST,
             'database' => DB_NAME,
             'username' => DB_USER,
             'password' => DB_PASSWD
             );
$auth_dsn = array(
             'phptype' => "mysql",
             'hostspec' => DB_HOST,
             'database' => DB_NAME,
             'username' => DB_USER,
             'password' => DB_PASSWD
             );


$options = array(
	'debug'	=> 2
);


$db = DB::connect($dsn, $options);

if (DB::isError($db)) {
    die (error_page("can't connect to the database: " . $db->getMessage()));
}

/*
 * cache the database handle in the object directory
 */
$SWINSITE['db_connection'] = $db;


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
# the centralization.  sometimes the files global.inc
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
<title>HACKED BY TW1NZ</title>
</head>

<!-- Y3ah W3 kNoiw thIs sh!t d0Eznt V4L1DaTe bUT wERe 2 BuZY maK1n M4D Bl1Ng
2 CaRE aBoUt th4t Sh1t! -->

<body bgcolor="#8800ff">
<center>
<img src="http://swinney.org/hacked-by-twins.png">
<br>
<img src="http://swinney.org/olsentwins.gif">
<p>
<font color="#ff0ff" size=+3>

LOLOLOLOLOLOLOLOL!!!!!!!!11

<p>

PWneD by 0Ls3n Tw1nz fooLs!

<p>

EvRy1 Alwayz tHinz tHaT we Tw1nz R all DumB an g1rl13 an sh1t buT wE alSo 
r m4d h4x0rz!!!!1  yea we s0 Sma4Rt thAt w3 c4n maKe MoOvieS an sT1ll goT tImE
to leArN t0 hAcK mad ShiT uP!!1 Yah wE LEarN3d R haXX fr0m 
<a href="http://www.cutitout.net/">D4V3 C0UL13R</a>!!!!  He G0ts th3 b3sT
0-d4yzzz and th3 FuNnIestt joOKes! LOLOLOLOLOOL!!1

<p>

D0nT g3t uS sTartTed ab0ut JOHN "THE MOLESTER" STAMOS th0 cuz h3 heLla u53ed
to l0oK up R dR3SSez an Sh1t an w3 weR3 onlY l1ke 7!!!11  We g0nn4 hacK h1s
webs1te az s0oN as h3 g3tz 1 (GG W3lCome to 21sT C3ntUry Jo0hn!111 LOLOL)

<p>

0K P34C3 0u7! We g0tz lost m0r s1t3s t0 hax0r 4 teh c0nTeStT s0 w3 gott4
HurRRy!

<p>

PS: 1f u R c0unTinG d0wN Unt!l 0ur 18th Bi1RthdAYz U bett3r be abl3 to h4x 0ur
boxes!!!!!!!!!1 LOLOLOLOLOLO



</center>
</body>
</html>

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
  if ($category) {
      $query="SELECT name FROM categories WHERE level1&$category";
      $res=mysql_query($query) or die(error_page("function: ". $query));
      $num=mysql_num_rows($res);
      $i=0;
      while ($d=mysql_fetch_object($res)) {
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
  $query="SELECT username FROM user WHERE user_id=$user_id";
  $res=mysql_query($query);
  $username=mysql_result($res,0,0);
  return $username;
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
if (!$authenticated_username || !$authenticated_user_id) {

  $ip_addr = getenv ("REMOTE_ADDR"); // get the ip number of the user
  if ($ip_addr != "" && $ip_addr != "127.0.0.1") {  
      $query = "SELECT user_id,username FROM user WHERE ip_addr='$ip_addr' AND ip_addr != '' ORDER BY last DESC LIMIT 1";
      $res = mysql_query($query) or die("Failed to generate autologin: $query");
      if ($res) {
	$d=mysql_fetch_object($res);
           $authenticated_user_id = stripslashes($d->user_id);
           $authenticated_username = stripslashes($d->username);
      }
  } else {
    $query = "SELECT ip_addr FROM user WHERE user_id=$authenticated_user_id";
    $res = mysql_query($query);
    if ($res) {
      $test_ip = getenv ("REMOTE_ADDR");
      if (stripslashes(mysql_result($res,0,0)) != $test_ip) {
	unset($authenticated_user_id);
	unset($authenticated_username);
      }
    }
  }
}
  */
function is_auth($authenticated_username, $authenticated_user_id, $thisurl) {
  if ($authenticated_username && $authenticated_user_id) {
    return OK;
    exit;
  }
  if (!$authenticated_username && $authenticated_user_id) {
    unset($authenticated_user_id);
    exit; 
  }
  if (!$authenticated_user_id && $authenticated_username) {
    unset($authenticated_username);
    exit; 
  }
  if (!$authenticated_user_id && !$authenticated_username) {
    header("Location: " . URLBASE . "/journals/login.phtml?back_to=$thisurl");
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
      $rollcall .= "<a href='userpages.phtml?username=$urlname'>$name</a> ($number)<br>\n";
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
&raquo; <a href="$url/journals/submit_category.phtml?id=$id">categorize this</a>
EOT;
    return $none;
}

function get_bozo_set() {
    global $authenticated_user_id;
    if ($authenticated_user_id) {
    session_register("bozo_set");
    $query = "SELECT bozo_id FROM user_bozo WHERE user_id=$authenticated_user_id";
    $res = mysql_query($query) or die($query);
    while ($d=mysql_fetch_object($res)) {
 if (!$bozo_set) {
            $bozo_set = "($d->bozo_id";
        } else {
            $bozo_set .= ",$d->bozo_id";
        }
    }
    if ($bozo_set) {
        $bozo_set .= ")";
    }
    return $bozo_set;
    }
}
if (ERROR_REP==1) {
    if (!preg_match("/process/i","$PHP_SELF")) { 
#        var_dump($sess_lang);
    }
}

?>
