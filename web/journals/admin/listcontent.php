<?
#$Id$
# include the templates/top.inc
$title="Administrate Entries";
require_once("../global.php");
# i created an articles_user table for keeping
# record of the most recent post by a person
# this will eliminate the problem of green posting
# furiously throughout the day.
# to create the table for this stuff
# create table articles_user (user_id int(11) NOT NULL PRIMARY KEY auto_increment, username varchar(20) NOT NULL, most_recent int(11), total_submitted int(11));

if ($status==2 && $front=="yes") {

	$query = "UPDATE articles_user SET most_recent=$article_id, total_submitted=total_submitted+1 WHERE username='$username'";
	$res = mysql_query($query) or die("\n<P>update failed</P>");
#	echo (mysql_affected_rows()?"success":"failure"); 
	$affected=mysql_affected_rows(); 
} 

if ($affected=="0"||$affected=="-1") { # UPDATE was invalid, do INSERT
	$query = "INSERT INTO articles_user (user_id,username,most_recent,total_submitted) VALUES ('','$username',$article_id,1)";
	$front_res = mysql_query($query) or die ("\n<P>insert failed</P>");
}


// update the articles

  if ( $type == "resubmit" ) {

    $res = mysql_query ("UPDATE articles_text SET text='$update' WHERE article_id=$article_id");



    # Update the status of the article
    #  if status is greater than or equal to 1 and greater than 
    #  or equal to 4 than update it in the database
    if ( $status >= 1 && $status <= 4 ) {


// select the article list
#
# Work out what subjects
#
      if (isset($cat)) {
	$end=array_pop($cat);
	foreach ($cat as $value) {
          $query=$query . $value . " | ";
	}
	$cat_str="(". $query . $end .")";
      }

$res = mysql_query("UPDATE articles_info SET web='$web', status='$status', title='$article_title', blurb='$blurb', category=$cat_str WHERE article_id='$article_id'");

    }

	

    if ( $subby == "Save and Exit" ) { 
    unset($article_id); 
    @header("Location: listcontent.php");
    }
}



//
// Showing the article
//

/*

+------------+--------------+------+-----+---------+----------------+
| Field      | Type         | Null | Key | Default | Extra          |
+------------+--------------+------+-----+---------+----------------+
| article_id | int(11)      |      | PRI | 0       | auto_increment |
| username   | varchar(20)  | YES  |     | NULL    |                |
| web        | varchar(255) | YES  |     | NULL    |                |
| date       | date         | YES  |     | NULL    |                |
| time       | int(11)      | YES  |     | NULL    |                |
| status     | tinyint(4)   | YES  |     | NULL    |                |
| keywords   | varchar(100) | YES  |     | NULL    |                |
| title      | varchar(255) | YES  |     | NULL    |                |
| blurb      | varchar(255) | YES  |     | NULL    |                |
| category   | bigint(20)   | YES  |     | NULL    |                |
| image      | tinyint(4)   | YES  |     | NULL    |                |
+------------+--------------+------+-----+---------+----------------+ 
*/



if ( isset($article_id) ) {

	$res = mysql_query("
		SELECT  username,
			keywords, 
			title, 
			blurb, 
			status, 
			image, 
			web 
		FROM articles_info 
		WHERE article_id='$article_id'");
	$d=mysql_fetch_object($res);
    $username = $d->username;
    $keywords = $d->keywords;
    $article_title = $d->title;
    $blurb = $d->blurb;
    $status = $d->status;
    $images = $d->image;
    $web = $d->web;
    $keyarray = explode(',', $keywords);



#
# header shit, this thing is FUCKED
# i wouldnt wish this on my enemies
#
include(INCDIR ."/top.inc");
include(INCDIR ."/swinney.req");
echo "<form action='listcontent.php' method='post'>";
include("cat_call.inc");
include(INCDIR ."/endleft.inc");
echo <<<EOT
<center>
<p class="subheader">
<a href='index.php'>firebird</a> | 
<a href='listcontent.php'>articles</a> | 
<a href='admin_comments.php'>comments</a> | 
<a href='users.php'>users</a>
</p>
</center>
EOT;


echo "<P><B>user:</B> $username</P>";


// This is where the editing begins
    $count = 0;
    for ( $i = 0 ; ; $i++ ) {
      if ( $keyarray[$i] == "" ) break;
      $keylist=$keylist . $keyarray[$i] . ".. ";
    }
    echo "<P><B>Keywords:</B> $keylist</P>";



//
// show images if they exist
//

   $imagepath = URLBASE . "/journals/images";
   $filepath = DIRBASE . "/journals/images";

    for ($i = 1; $i <= $images ; $i++) {
      $noext = $article_id."_".$i;

      if (file_exists("$filepath/$noext.jpg")) {
        $imgfile = "$imagepath/$noext.jpg";

       } else if (file_exists("$filepath/$noext.gif")) {
        $imgfile = "$imagepath/$noext.gif";

       } else if (file_exists("$filepath/$noext.png")) {
        $imgfile = "$imagepath/$noext.png";
       } else {
        echo "unrecognized file upload: $filepath/$noext.*<BR>";   
       }

      if ($imgfile) {
	echo <<<EOT
<P>$imgfile</P>
<P>&lt;img src="$imgfile" height="150" align="left"&gt;</P>
<P><a href="$imgfile"><img src="$imgfile" height="150"></a></P>
EOT;
      }
    }

//
// show article stuff
//

if ($web != "") {
    if (substr($web,0,7) !='http://' && substr($web,0,7) !='mailto:') {
        if (strstr($web,'@')) { 
	    $web = "mailto:$web"; 
	} else	{ 
	    $web = "http://$web"; 
	}
    }
}
    echo "<B>web:</B> <a href=\"$web\">$web</a><BR>";
    echo "<textarea name=web cols=60 rows=2>$web</textarea><BR>";
    echo "<B>Title:</B> ".stripslashes($article_title);
    echo "<textarea name=article_title cols=60 rows=2>".stripslashes($article_title)."</textarea><BR>";
    echo "<b>Blurb:</B> ".stripslashes($blurb);
    echo "<textarea name=blurb cols=60 rows=3>".stripslashes($blurb)."</textarea>";


// Look up the article

$res = mysql_query("SELECT text FROM articles_text WHERE article_id='$article_id'");

$row = mysql_fetch_row($res);
$text = stripslashes($row[0]);

if ( isset($article_id) ) {

    echo "<input type='hidden' name='type' value='resubmit'>\n";
    echo "<input type='hidden' name='article_id' value='$article_id'>\n";
    echo "<table border=0 width=400><tr><td>$text</td></tr></table>\n<br>\n<br>\n";
    echo "<textarea name=update cols=60 rows=20 wrap=virtual>$text</textarea>\n<br>\n";

} 


//gonna f*ck with my status now?!


    echo "<P><b>Status : </b> <select name='status'>";
    if ( $status == 1 ) {
      echo "<option value='1' selected>Pending";
    } else if ( $status == 2 ) {
      echo "<option value='2' selected>Active";
    } else if ( $status == 3 ) {
      echo "<option value='3' selected>Archived";
    } else if ( $status == 4 ) {
      echo "<option value='4' selected>Trash";
    }
    echo "<option>---\n";
    echo "<option value='1'>Pending\n";
    echo "<option value='2'>Active\n";
    echo "<option value='3'>Archived\n";
    echo "<option value='4'>Trash\n";
    echo "\n</select>\n";
    echo "\nfront? yes<INPUT name='front' type='radio' value='yes' CHECKED>";
    echo "\nno<INPUT name='front' type='radio' value='no'></P>";

    echo "<p>";
    echo "<input name='subby' type='submit' value='Save and Reload'>\n";
    echo "<input name='subby' type='submit' value='Save and Exit'>\n";
    echo "<br><br>\n";
    echo "</form>\n";
include_once (INCDIR ."/bottom.req");
include_once (INCDIR ."/footer.inc");
    exit;
  }

// article list
include(INCDIR ."/top.inc");
include(INCDIR ."/swinney.req");
include(INCDIR ."/norollcall.inc");
include(INCDIR ."/endleft.inc");
echo <<<EOT
<center>
<p class="subheader">
<a href='index.php'>firebird</a> | 
<a href='listcontent.php'>articles</a> | 
<a href='admin_comments.php'>comments</a> | 
<a href='users.php'>users</a>
</p>
</center>
EOT;

  echo "<p>";
  $res = mysql_query("SELECT * FROM articles_info WHERE status<>4 ORDER BY article_id DESC LIMIT 20");
  
  echo "<table cellpadding=4 cellspacing=0 border=1 align=center width=\"98%\">";
  echo "<tr>";
  echo "<td align=center><b>ID</b></td>\n";
  echo "<td align=center><b>Username</b></td>\n";
  echo "<td align=center><b>Date</b></td>\n";
  echo "<td align=center><b>Status</b></td>\n";
  echo "<td align=center><b>Title</b></td>\n";
  echo "<td align=center><b>Blurb</b></td>\n";
  echo "<td align=center><b>Comments</b></td>\n";

  echo "</tr>";
  while ( $d = mysql_fetch_object($res) ) {
    echo "<tr>";
    echo "<td align=center><b><a href='../article.php?id=$d->article_id.txt'>$d->article_id</a></b></td>\n";
    echo "<td align=center><b>$d->username</b></td>\n";
    echo "<td align=center>$d->date</td>\n";


    switch ( $d->status ) {
      case 0 : $str = "";  break;
      case 1 : $str = "<font color='red'>Pending</font>";  break;
      case 2 : $str = "<font color='green'>Accepted</font>";  break;
      case 3 : $str = "<font color='gray'>Archived</font>";  break;
      case 4 : $str = "<font color='gray'>Trash</font>";  break;
    }

    echo "<td align=center>$str</td>\n";
    echo "<td align=center><a href='listcontent.php?article_id=$d->article_id'>$d->title</a></td>\n";
    echo "<td align=center>$d->blurb</td>\n";



//  grab out the number of comments associated with this article
//  i tried to do this using count(*) but it was returning a numbering from 4 on (5,6,7...)
//  so i changed to mysql_num_rows() on the results from selecting all the comment_id's associated
//  with the article_id's.  :)    

    $comments = mysql_query("SELECT comment_id 
		FROM comments 
		WHERE article_id=$d->article_id");
    $num_comments=mysql_num_rows($comments);
    echo "<td align=center><a href='admin_comments_article.php?article_id=$d->article_id'>$num_comments</a></td>\n";
    echo "</tr>\n";

 }
    echo "</table>\n";
include_once (INCDIR ."/bottom.req");
include_once (INCDIR ."/footer.inc");
?>












