<?
###################################################
# $Id$
# process them articles
#
require_once("global.php");
session_register("error_msg");

if (!$language) {
  $language='en';
}

if ($last_lang!=$language) {
    if (!$last_lang) {
      session_register("last_lang",$language);
    }
  $last_lang=$language;
}


if (!$title) {
  $title="This bitch left no title.";
}

if (!$username) {
  $username="anonymous";
}

/*
 * register session var for $bin used in category 
 * combination.
 */

session_register("bin");
$bin=0;

/*
 * Init the date and time
 */

$date = date("Y-m-d");
$time = time();

/*
 * work out what category for the database
 */

if (isset($cat)) {
    foreach ($cat as $one => $two) {
       if (!isset($bin)) {
           $bin=$two;
       } else {
           $bin=$bin|$two;
       }
    }
    /*
     * set bin to category for db
     */
    $category=$bin;
} else {
    $category=0;
} // end loop

if ($submit) {
  $ip_addr = getenv ("REMOTE_ADDR");

  // Insert into the database
  $esc_keywords = addslashes($keywords);
  $esc_title = addslashes($title);
  $esc_blurb = addslashes($blurb);
  if (!$_SESSION['authenticated_user_id']) {
    if ($_SESSION['authenticated_username']) {
    $_SESSION['authenticated_user_id']=get_user_id($_SESSION['authenticated_username']);
    } else {
      $_SESSION['authenticated_user_id']=205;
    }
  }

  $query = <<<EOT
INSERT INTO articles_info
    SET
     user_id='$_SESSION['authenticated_user_id']',
     username='$username',
     date=NOW(),
     time=NOW(),
     ctime=NOW(),
     ltime=NOW(),
     status=1,
     keywords='$esc_keywords',
     title='$esc_title',
     blurb='$esc_blurb',
     category='$category',
     image='$image',
    ip_addr='$ip_addr',
    language='$language'
EOT;
  $res=$db->query($query);
  if (DB::isError($res)) {
    // get the portable error string
    $error_msg .= $res->getMessage();
    header("Location: $HTTP_REFERER");
  } else {
    $success_msg .= "<P>Articles info saved.</P>";
  }

  $ins_article_id = mysql_insert_id();

  /* check for that ins_article_id */
  if (!$ins_article_id) {
    $error_msg .= "<P>Failure to gain an ins_article_id.</P>";
    header("Location: $HTTP_REFERER");
    exit();
  }


  /*
   * FIRST: lets get the article text from the form
   * because that is the most usual format for it.
   */

  if ($content) {
    $esc_content = addslashes($content);
    unset($content);
  }


  /* 
   * Get the article text from the file submit
   * into a buffer and insert into database.
   */


  if ($userfile && $userfile!="none") {
    unset($esc_content);
    //
    // open the temp file read only
    $fd = fopen($userfile,"r");
    //
    // assemble the buffer in chunks
    while (!feof($fd)) {
      //
      // stack it together
	$buffer=$buffer . fgets($fd,4069);
    }
    //
    // close the file.
    fclose($fd);
    // check that there is no esc_content
    if ($esc_content) {
      unset($esc_content);
    }
    //
    // add slashes before putting into the database.
    // if you dont do this on these html file that
    // contain every possible bonker, 
    // the insert WILL bomb.
    $esc_content=addslashes($buffer);
    unset($buffer);
    if (!$esc_content) {
      $error_msg .= "<P>Did you try to upload from file?  Your file buffer was empty.</P>";
      header("Location: $HTTP_REFERER");
      exit();
    }
  } 
  if (!$esc_content) {
    $error_msg .= "<P>we have neither content nor a userfile for this submit.</P>";
    header("Location: $HTTP_REFERER");
    exit();
  }

  /* 
   * Now then, assuming we have some $esc_content to post,
   * let us role with it.
   */

  if ($ins_article_id) {
    if (!$esc_content) {
      $error_msg .= "<P>there has been an error in the processing of your submission.  please upload over now, or contact bugs@swinney.org</P>";
      header("Location: $HTTP_REFERER");
      exit();
    }
    $query_text = <<<EOT
INSERT INTO articles_text
     VALUES ($ins_article_id, '$esc_content');
EOT;
  } else {
    $error_msg .= "<P>id was not available at time of query</P>";
    header("Location: $HTTP_REFERER");
    exit();
  }

  if ($query_text) {
  $res=$db->query($query_text);
    if (DB::isError($res)) {
      // get the portable error string
      $error_msg .= $res->getMessage();
      header("Location: $HTTP_REFERER");
    } else {
      $success_msg = "<P>Article's text saved.</P>";
    }
  } else {
      $error_msg = "Problem saving the article text: " . mysql_error();
  }
} else {
  $error_msg = "<P>Submit value not specified.</P>";
}

if ($error_msg) {
  session_register("error_msg");
  include("./submit_article.php");
} else {
  session_register("success_msg");
  if ($images_too=="no") {
    $loc = URLBASE;
  } else {
    $loc = "submit_image.php?article_id=$ins_article_id";
  }
  $query = "SELECT email FROM user WHERE user_id=$_SESSION['authenticated_user_id']";

  $res = mysql_query(addslashes($query));
  $user_email = stripslashes(mysql_result($res,0));

  $username = stripslashes($username);
  $title = strip_tags(stripslashes($title));
  $blurb = strip_tags(stripslashes($blurb));
  $content = strip_tags(stripslashes($content));
  mail("swinney@swinney.org", "$title by $username\n", "$blurb\n $content", "From: $user_email\nhttp://swinney.org/madmin/\n");
  header("Location: $loc");
}
?>
