<?
///////////////////////////////////////////
// $Id$
require_once("../global.php");
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
<table cellpadding=0 cellspacing=4 border=0 align=center width="98%">
<tr>
<td align=center><b>ID</b></td>
<td align=center><b>Username</b></td>
<td align=center><b>Status</b></td>
<td align=center><b>Title</b></td>
<td align=center><b>Blurb</b></td>
<td align=center><b>Edit</b></td>
</TR>
EOT;
$query="SELECT article_id, username, status, title, blurb FROM articles_info ORDER BY article_id DESC LIMIT 10";  
$res = mysql_query($query);
  while ( $d = mysql_fetch_object($res) ) {

    switch ( $d->status ) {
      case 0 : $str = "";  break;
      case 1 : $str = "<font color='red'>Pending</font>";  break;
      case 2 : $str = "<font color='green'>Accepted</font>";  break;
      case 3 : $str = "<font color='gray'>Archived</font>";  break;
      case 4 : $str = "<font color='gray'>Trash</font>";  break;
    }


    echo <<<EOT
<tr>
<td align=center><b>$d->article_id</b></td>
<td align=center><b>$d->username</b></td>
<td align=center>$str</td>
<td align=center>$d->title</td>
<td align=center>$d->blurb</td>
<td align=center><a href='edit_article.php?article_id=$d->article_id'>
<IMG BORDER=0 SRC="http://swinney.org/dev/journals/img/articles.gif"></a></td>
</TR>
EOT;


 }
    echo "</table>\n";
include_once (INCDIR ."/bottom.req");
include_once (INCDIR ."/footer.inc");
?>












