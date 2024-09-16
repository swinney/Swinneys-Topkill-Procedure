<?
#$Id$
require_once("../global.php");

if (isset($article_id)) {
    $res = mysql_query("
                SELECT  username,
                        date,
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
    $date = $d->date;
    $keywords = $d->keywords;
    $article_title = $d->title;
    $blurb = $d->blurb;
    $status = $d->status;
    $images = $d->image;
    $web = $d->web;
    $keyarray = explode(',', $keywords);

    $title=stripslashes($article_title);
    $blurb=stripslashes($blurb);
    
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
//
// put together the keywords
$count = 0;
for ( $i = 0 ; ; $i++ ) {
    if ( $keyarray[$i] == "" ) break;
    $keylist=$keylist . $keyarray[$i] . ".. ";
}


if ($web != "") {
    if (substr($web,0,7) !='http://' && substr($web,0,7) !='mailto:') {
        if (strstr($web,'@')) { 
	    $web = "mailto:$web"; 
	} else	{ 
	    $web = "http://$web"; 
	}
    }
}

echo <<<EOT
<TABLE BORDER=0 WIDTH=400 CELLSPACING=0 CELLPADDING=0 NOSHADE>
<TR>
<TD BGCOLOR="#cccccc">
  <P>Username</P>
</TD>
<TD>
<P>$username</P>
</TD>
<TD align="right">
<INPUT TYPE="text" NAME="username" VALUE="$username">
</TD>
</TR>
<TR>
<TD>Date</TD>
<TD>$date</TD>
<TD align="right">
<INPUT TYPE="text" NAME="date" VALUE="$date">
</TR>
<TR>
<TD>
<P>Keywords</P>
</TD>
<TD>
<P>$keylist</P>
</TD>
<TD align="right">
<INPUT TYPE="text" NAME="keywords" VALUE="$keywords">
</TD>
</TR>

<TR>
<TD>
<P>Web</P>
</TD>
<TD>
<a href="$web">$web</a>
</TD>
<TD align="right">
<INPUT TYPE="text" name="web" VALUE="$web" cols=60>
</TD>
</TR>
</TABLE>

<B>Title:</B> $title
<textarea name=article_title cols=60 rows=2>$title</textarea><BR>
Blurb: $blurb
<textarea name=blurb cols=60 rows=3>$blurb</textarea>
EOT;

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
    echo "\nfront? yes<INPUT name='front' type='radio' value='yes'>";
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

