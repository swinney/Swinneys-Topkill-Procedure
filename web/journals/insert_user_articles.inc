<?
#$Id$

if(!$page_num || $page_num < 1) { //No Page Number? Set it to Page 1 then...
        $page_num = 1;
}

//How many pages per page will be displayed...
$per_page = 20;

//Set the page start variable...
$page_start = ($page_num-1) * $per_page;
 
//Do a number query to see how many results match the category...

$query="SELECT count(*) as num_articles FROM articles_info WHERE status='2' AND username='". addslashes($username) ."' ORDER BY time DESC";
$num_res = mysql_query($query);
$num_object = MYSQL_FETCH_OBJECT($num_res);
$num_of_results = $num_object->num_articles;

// lets try this userlist thingy $USERS

$res = mysql_query ( "SELECT article_id,title,blurb,date,username FROM articles_info WHERE status='2' AND username='". addslashes($username) ."' ORDER BY time DESC limit $page_start,$per_page");
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
<span class="subheader"><b>Articles</b> | <a href="usercomments.phtml?username=$username">Comments</a>

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
<a href="$PHP_SELF?username=$username&page_num=$page_forward">&laquo; earlier articles</a>

EOT;
  }  

  if ($page_num < $num_of_pages and $page_num > 1) { 
    echo ' - ';
    }
  
  if ($page_num > 1){
    echo <<<EOT
<a href="$PHP_SELF?username=$username&page_num=$page_back">later articles &raquo;</a>
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

<table width="300" border="0" cellspacing="0" cellpadding="0">
<tr>
<td>
EOT;

// multiple rows

while ( $individual_row = mysql_fetch_object( $res ) ) {

   $articleno = $individual_row->article_id;


echo <<<EOT
<p><a href="article.phtml?id=$articleno.txt">
<b>$individual_row->title</b></a><br>

EOT;

    $blurb = $individual_row->blurb;
    if ($blurb) {
      $blurb .= "<br>\n";
      }

echo <<<EOT
$blurb
<span class="small">$individual_row->date
EOT;

$res2 = mysql_query ( "SELECT count(*) as num FROM comments WHERE article_id='$individual_row->article_id' AND status=0");

$d =  mysql_fetch_object($res2);

echo <<<EOT
 | $d->num comments</span>
</p>
EOT;
}


  echo <<<EOT
</td>
</tr>
</table>
<p>

EOT;

if ($page_num < $num_of_pages or $page_num > 1) {

echo <<<EOT

<p>

EOT;

  if ($page_num < $num_of_pages) { 
    echo <<<EOT
<a href="$PHP_SELF?username=$username&page_num=$page_forward">&laquo; earlier articles</a>

EOT;
  }  

  if ($page_num < $num_of_pages and $page_num > 1) { 
    echo ' - ';
    }
  
   if ($page_num > 1){
    echo <<<EOT
<a href="$PHP_SELF?username=$username&page_num=$page_back">later articles &raquo;</a>

EOT;
  }
  
  }

 echo "</p>";





