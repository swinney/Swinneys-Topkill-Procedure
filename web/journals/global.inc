<?php
// -*- Mode: PHP; indent-tabs-mode: nil; =*-
////////////////////////////////////////////////////////
// $Id$

/*
 * initialize the session. make the session cookie persist for a long,
 * long time. dot his before anything else so that if something dies,
 * we don't get errors about sending headers.
 */
session_start();
session_set_cookie_params(time()+9999999);

/*
 * if the directory containing global.inc also contains
 * local_conf.php, add that directory to the system include path so we
 * can include local_conf.php.
*/

$thisdir = dirname(realpath(__FILE__));
if (file_exists("$thisdir/local_conf.php")) {
    use_lib($thisdir);
    include_once('local_conf.php');
}

/*
 * set default configuration values.
 *
 * XXX: would like to set these before including the local config
 * file, but define("foo") seems to cause an error if define("foo")
 * has already been executed. and we want to keep the
 * if(!defined("foo")) statements out of the local config file, to
 * keep it simple.
 */

if (!defined("URLBASE")) {
    define("URLBASE", "http://swinney.org"); // no trailing slash!
}

if (!defined("DIRBASE")) {
    define("DIRBASE", "/sky/www/swinney.org/html");
}

if (!defined("IMGBASE")) {
    define("IMGBASE", "/sky/www/swinney.org/html/dev/journals/images");
}

if (!defined("IMGURL")) {
    define("IMGURL", URLBASE . "/journals/images");
}

if (!defined("CSS_URLE")) {
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
}

/*
 * connect to the database. if unsuccessful, display an error message.
 * no reason to make this a function, since nobody would ever have a
 * need to call it!
 */
require_once('DB.php');
$dsn = array(
             'phptype' => "mysql",
             'hostspec' => DB_HOST,
             'database' => DB_NAME,
             'username' => DB_USER,
             'password' => DB_PASSWD
             );


$db = DB::connect($dsn, true);

if (PEAR::isError($db)) {
    die (error_page("can't connect to the database: " . $db->getMessage()));
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
    $names="unsigned";
  }
     return $names;
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

/////////////////////////////////////////
// SPACED_OUT()
/////////////////////////////////////////
function spaced_out ($text) {
  $spaced_out=ereg_replace(" ","%20",$text);
  return $text;
}
 

////////////////////////////
// check authorization
///////////////////////////

if (preg_match("/(vip|submit|admin)/i","$SCRIPT_NAME") && !$user_id) {
  session_register("back_to");
  $back_to= $SCRIPT_NAME;
  if ($article_id) {
    $back_to .= "?article_id=$article_id";
  }
  $url=URLBASE;
  //echo $back_to;
  header("Location: $url/journals/login.phtml");
  exit();
}

?>
