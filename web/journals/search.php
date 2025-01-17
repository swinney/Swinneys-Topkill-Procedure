<?
# $Id$
# searching for stuff on the internet reminds me of justin hall
# create table search_words (word_id int(11) primary key not null auto_increment, word varchar(25) not null, num_rows int(5) NOT NULL DEFAULT 0, num_times int(4) NOT NULL DEFAULT 0); 
$title="Search Results for $find";
require_once("./global.php");
include "templates/top.inc";
include "templates/swinney.req";
include "templates/norollcall.inc";

# get that IP Address
$ip_addr = getenv ("REMOTE_ADDR"); 

echo <<<EOT
<table cellpadding="2" cellspacing="0" border="0" width="375">
EOT;


if ($find) {

# query articles_text.text for string and match 
# article_text.article_id with articles_info.article_id 
# to get the title and author username and stuff. 
$find =  addslashes($find);
$query =<<<EOT
  SELECT articles_info.date,
         articles_info.title,
         articles_text.article_id,
         articles_info.username 
    FROM articles_info,
         articles_text 
   WHERE articles_info.article_id=articles_text.article_id 
     AND articles_info.status=2 
     AND articles_text.text 
    LIKE '%$find%' 
ORDER BY articles_text.article_id 
DESC LIMIT 300
EOT;

$articleres = mysql_query($query);

# get the number of returned rows for shits and giggles.
$articlenum = mysql_num_rows($articleres);

# query comments.comment for $find and 
# get articles_info.title based on comments.article_id 
$query2 = <<<EOT
  SELECT comments.comment_id,
  comments.article_id,
  comments.username,
  articles_info.title, 
  articles_info.date
  FROM comments, articles_info 
  WHERE comments.article_id=articles_info.article_id 
  AND comment LIKE '%$find%' 
  ORDER BY article_id DESC
EOT;

$commentres = mysql_query($query2);

# number of rows returned just for displays sake
$commentnum = mysql_num_rows($commentres);

if ($articlenum == "0" and $commentnum == "0")
{
echo <<<EOT
<tr>
<td>
<span class="subheader"><b>No Luck.</b></span><br>
<span class="text">"<b>$find</b>" wasn't found in any article or comment on swinney.org.</span>
EOT;
}
else
{

if ($articlenum == "1")
{
$articleoccur = "match";
}
else
{
$articleoccur = "matches";
}
    

if ($commentnum == "1")
{
$commentoccur = "match";
}
else
{
$commentoccur = "matches";
}


if ($articlenum > "299")
{
$articlevnum = "more than 300";
}
else
{
$articlevnum = $articlenum;
}


if ($commentnum > "299")
{
$commentvnum = "more than 300";
}
else
{
$commentvnum = $commentnum;
}

    
echo <<<EOT
<tr>
<td nowrap>
<span class="subheader"><b>Search Results for "$find" &raquo;</span></b></td>
<td align="right" nowrap>
EOT;

if ($articlenum > "0") {
echo "<span class=\"subheader\"><a href=\"#articles\">Articles</a>:</span></td>";
}
else
{
echo "<span class=\"subheader\">Articles:</span></td>";
}

echo <<<EOT
<td valign="bottom" nowrap>
<span class="text"><b>$articlevnum $articleoccur</b></span></td>
</tr>

<tr>
<td>
&nbsp;</td>
<td align="right" nowrap>
EOT;

if ($commentnum > "0") {
echo "<span class=\"subheader\"><a href=\"#comments\">Comments</a>:</span></td>";
}
else
{
echo "<span class=\"subheader\">Comments:</span></td>";
}

echo <<<EOT
<td valign="bottom" nowrap>
<span class="text"><b>$commentvnum $commentoccur</b></span></td>

</tr>

EOT;

}

if ($articlenum > "0")
{
echo <<<EOT
<tr>
<td colspan="3">
<a name="articles">&nbsp;</a></td>
</tr>

<tr>
<td colspan="3">
<span class="subheader">
<b>Matching Articles</b></span></td>
</tr>

<tr>
<td colspan="3">

EOT;

# start the return loop on $res
while ($d=mysql_fetch_object($articleres)) {
   # assign values
   $date=$d->date;
   $article_id=$d->article_id;
   $title=stripslashes($d->title);
   $username=stripslashes($d->username);
   # print out record
   
echo <<<EOT

<p>
<a href="article.php?id=$article_id">
<b>$title</b></a> by $username<br>
<span class="small">$date</span>
</p>
EOT;

} # close the $articleres loop
}

if ($commentnum > "0")
{
echo <<<EOT
</td>
</tr>

<tr>
<td colspan="3">
<a name="comments">&nbsp;</a></td>
</tr>

<tr>
<td colspan="3">
<span class="subheader">
<b>Matching Comments</b></span></td>
</tr>

<tr>
<td colspan="3">

EOT;

#loop through the records from $res
while ($d=mysql_fetch_object($commentres)) {
  $article_id=$d->article_id;
  $comment_id=$d->comment_id;
  $title=$d->title;
  $date=$d->date;
  $username=$d->username;
  
$commentres2 = mysql_query ("SELECT username,title FROM articles_info WHERE article_id=$article_id");

$row = mysql_fetch_row($commentres2);

$writer = $row[0];

# this loop first determines if the first record has been printed
# if so, then format text with "... sez ", if not then just format
# with "sez" because it is picking up the idea from scratch

echo <<<EOT
<p>
<b><a href="article.php?id=$article_id#$comment_id">$username</a></b> on <a href="article.php?id=$article_id">$title</a> by <a href="userpages.php?username=$writer">$writer</a><br>
<span class="small">$date</span>
</p>

EOT;

}

echo <<<EOT
</td>
</tr>

EOT;

}

# now we move on to the database.  we are keeping track of 
# all search terms so as to better improve our search performance
# in the future.  i am not certain how this helps, but i may
# have a dream or something.
#				see?
# mysql> desc search_words;
# +-----------+-------------+------+-----+---------+----------------+
# | Field     | Type        | Null | Key | Default | Extra          |
# +-----------+-------------+------+-----+---------+----------------+
# | word_id   | int(11)     |      | PRI | NULL    | auto_increment |
# | word      | varchar(50) |      |     | 0       |                |
# | num_rows  | int(5)      |      |     | 0       |                |
# | num_times | int(4)      |      |     | 0       |                |
# | ip_addr   | text        |      |     |         |                |
# +-----------+-------------+------+-----+---------+----------------+
# 5 rows in set (0.01 sec)


$query = "UPDATE search_words SET num_rows=$num, num_times=num_times+1, ip_addr='$ip_addr' WHERE word='$find'";
# update the search terms number of rows and number of times searched
$res = mysql_query($query);

# get affected rows in case none were affected, in which case we need
# to do an insert because there is a first time for everything.

$affected = mysql_affected_rows();

if ($affected==0) { # UPDATE was invalid, do INSERT
	
	$query = "INSERT INTO search_words (word_id,word,num_rows,num_times,ip_addr) VALUES ('','$find','$num','1','$ip_addr')";

	# insert new search_words into table allong with the number of returns
	# and the searcher's ip addr in case they try some sort of funny 
	# business we can send qq and yeti to destroy them.
	$res = mysql_query($query) 
		# if this thing doesnt work at all, then die. 
		# but we tested it.
		or die ("<P>invalid query</P>");

}

}
else
{
echo <<<EOT

<tr>
<td>
<span class="header"><b>Site Search</b></span><br>
Enter a word or phrase in the box above to search for.
EOT;
}

echo <<<EOT
</table>
EOT;


# lets unset the search term
unset($find);
include "templates/bottom.req";
include "templates/footer.inc";
?>


