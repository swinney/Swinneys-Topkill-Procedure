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
    include_once($thisdir ."/local_conf.php");
}

$thisurl = "http://". $HTTP_HOST . $SCRIPT_NAME;
if ($QUERY_STRING) {
    $thisurl .= "?". $QUERY_STRING;
}

/*
 * migrating from article_id to id
 */
if ($article_id) {
  $id=$article_id;
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

if (!defined("SITE_NAME")) {
    define("SITE_NAME", "Swinney.org");
}

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

function is_auth($authenticated_username, $thisurl) {
  if (!$authenticated_username) {
    header("Location: " . URLBASE . "/journals/login.phtml?back_to=$thisurl");
    exit; 
  }
}

/*
if (preg_match("/(vip|admin)/i","$SCRIPT_NAME") && !$user_id) {

  $url=URLBASE ."/journals/login.phtml";
  header("Location: $url");
  exit();
}
*/

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

//
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
  require_once ("/sky/users/swinney/htdocs/dev/php4/pear/HTML/Table.php");
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

function get_cat_none() {
    global $id;
    $url=URLBASE;
    $names=<<<EOT
&raquo; <a href="$url/journals/submit_category.phtml?id=$id">categorize this</a>
EOT;
    return $names;
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


?>
