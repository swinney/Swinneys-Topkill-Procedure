<?
#$Id$

#first do pagination

// what table are you paginating?
$table="comments";

//No Page Number? Set it to Page 1 then
if(!$page_num || $page_num < 1) { 
        $page_num = 1;
}

//How many pages per page will be displayed...
$per_page = 30;

//Set the page start variable...
$page_start = ($page_num-1) * $per_page;


 
//Do a number query to see how many results match the category...
$num_res = mysql_query ( "SELECT count(*) as num_articles FROM $table WHERE status='0' AND username = '$username' ORDER BY timestamp DESC");
$num_object = MYSQL_FETCH_OBJECT($num_res);
$num_of_results = $num_object->num_articles;


$query2="SELECT username,comment_id,comment,article_id FROM $table WHERE status='0' AND username = '$username' ORDER BY timestamp DESC limit $page_start,$per_page";

$query = "select comments.comment_id,comments.comment,comments.article_id,comments.username,articles_info.title,articles_info.username from comments, articles_info where comments.article_id=articles_info.article_id AND comments.username = '". addslashes($username) ."' order by comment_id DESC limit $page_start,$per_page";


$res2 = mysql_query ($query);

// Find out how many pages there are going to be
// number of results returned divided by the number per page displayed
$num_of_pages = $num_of_results/$per_page; 

// Find out if the num_of_pages was a decimal.. Can't have 2.1 pages...
$remainders = $num_of_results%$per_page; 


if($remainders != 0){ //If is was a decimal, turn it into an integer and add 1 to it...
       $num_of_pages = intval($num_of_pages) + 1;
}

$page_back = $page_num - 1;
$page_forward = $page_num + 1;


//while ($row = mysql_fetch_object($res)) {
if (isset($res)) {

$url = "article.phtml?id=$d->article_id";

// let's cut a nice little page header into here - J. 

echo <<<EOT

<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td nowrap>
<span class="subheader"><b>$username &raquo;</b></span></td>

<td>&nbsp;&nbsp;&nbsp;</td>

<td align="left">
<span class="subheader"><a href="userpages.phtml?username=$username">Articles</a> | <b>Comments</b>
EOT;

if ($page_num < $num_of_pages or $page_num > 1) {

echo <<<EOT
</span></td>
</tr>

<tr>
<td colspan="2">&nbsp;</td>
<td align="left">
<span class="text">

EOT;

  if ($page_num < $num_of_pages) { 
    echo <<<EOT
<a href="$PHP_SELF?username=$username&page_num=$page_forward">&laquo; earlier comments</a>

EOT;
  }  

  if ($page_num < $num_of_pages and $page_num > 1) { 
    echo ' - ';
    }
  
  if ($page_num > 1){
    echo <<<EOT
<a href="$PHP_SELF?username=$username&page_num=$page_back">later comments &raquo;</a>
EOT;
  }
  
  }
  
}

echo <<<EOT

</span>
</td>
</tr>
</table>

<br>

<table cellpadding="0" cellspacing="0" border="0" width="375">
<tr>
<td>
<img src="img/no.gif" alt="" width="1" height="4" border="0"></a><br></td>
</tr>

<tr>
<td bgcolor="#999999">
<img src="img/no.gif" alt="" width="1" height="1" border="0"><br></td>
</tr>

<tr>
<td>
<img src="img/no.gif" alt="" width="1" height="4" border="0"><br></td>
</tr>

EOT;


$res = mysql_query($query);
$num = mysql_num_rows($res);

while ($d=mysql_fetch_object($res2)) {
    $article_id=$d->article_id;
	$comment_id=$d->comment_id;
	$comment  = stripslashes($d->comment);
    $title=$d->title;
    $articlewriter=$d->username;

    echo <<<EOT

<tr>
<td><a name="$comment_id"></a>
<a href="article.phtml?id=$article_id.txt#$comment_id">$username</a> on
"<b><a href="article.phtml?id=$article_id">$title</a></b>" 
by <a href='userpages.phtml?username=$articlewriter'>$articlewriter</a>:<br>
$comment</td>
</tr>

<tr>
<td>
<img src="img/no.gif" alt="" width="1" height="4" border="0"></a><br></td>
</tr>

<tr>
<td bgcolor="#999999">
<img src="img/no.gif" alt="" width="1" height="1" border="0"><br></td>
</tr>

<tr>
<td>
<img src="img/no.gif" alt="" width="1" height="4" border="0"><br></td>
</tr>

EOT;

$last=$title;

}

echo <<<EOT

</table>

EOT;

if ($page_num < $num_of_pages or $page_num > 1) {

echo <<<EOT

<p>

EOT;

  if ($page_num < $num_of_pages) { 
    echo <<<EOT
<a href="$PHP_SELF?username=$username&page_num=$page_forward">&laquo; earlier comments</a>

EOT;
  }  

  if ($page_num < $num_of_pages and $page_num > 1) { 
    echo ' - ';
    }
  
   if ($page_num > 1){
    echo <<<EOT
<a href="$PHP_SELF?username=$username&page_num=$page_back">later comments &raquo;</a>

EOT;
  }
  
  }
?>
