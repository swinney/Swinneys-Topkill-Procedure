<?
#$Id$

###################################
# rollcall.inc - who is out there?
# this is the most major shit script
# in all of swinney.org.  UNTIL TODAY
# i just figured out how to generate the
# entire thing in one select statement.
# worship me.  suck my dick.  it does not matter
# i do this all for the bitches.  word up 
# in two thousand.  -OMS 
# Thu Jul 12, 2001 10:13 AM
#
# mmmm...the bitches. - J. 020010921

?>

<!-- BEGIN PHP Dynamically Required File: rollcall.inc -->


<table cellpadding="0" cellspacing="0" border="0" width="100%">
<tr>
<td align="center">

<img src="img/no.gif" alt="" width="1" height="10" border="0"><br>

<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td width="150" valign="top" align="right" nowrap>
<p>
<img src="<? echo URLBASE ?>/journals/img/rollcall.gif" alt="Roll Call" width="65" height="13" border="0"><br>

<img src="<? echo URLBASE ?>/journals/img/no.gif" alt="" width="1" height="7" border="0"><br>

(<a href="roll_call_all.phtml">complete list</a>)<br>

<img src="<? echo URLBASE ?>/journals/img/no.gif" alt="" width="1" height="7" border="0"><br>

<!-- WHAT IS GOING ON IN THE WORLD...  WHO?  -->

<?
/*
#########################################
# here is said bad ass select statement
# it gets the distinct pending_articles username
# then the count of articles by said username
# which come to think of it, might be un necessary.
# hm.  comments are good. no no, you cannot get
# the count by username organized without first
# getting the distinct.  i dont think. -OMS
# Thu Jul 12, 2001 10:36 AM
*/

# this is for limiting the return to only those
# that have posted in the last three months 
# where 3 months= 60 sec * 60 min * 24 hrs * 30 day * 3 mon
# aka    7776000= 60     * 60     * 24     * 30     * 3

# wow, all math and shit.  I'm impressed, Austin!  now I will enter
# a smaller random number, because that list is still too fucking 
# long. hm, that didn't seem to change anything.  does this code even
# work? - J. 020010921

$minus=time();
$minus=$minus-45343211;

$query = <<<EOT
SELECT DISTINCT username, count(username) AS number, status, time
  FROM articles_info
 WHERE status=2
EOT;
if (count($bozos)) {
  $query .= " AND username NOT IN $bozo_set";
}
$query .= " GROUP BY username";

$res = mysql_query($query) or
  die(error_page(mysql_error()));

while ($row = mysql_fetch_row ($res)) {
/*
##########################################
# this cannot be called $username
# without interfearing with the url's
# $username.  so it will be called $user.
# austin, Thu Jul 12, 2001  1:40 PM
*/

$name=$row[0];
$number=$row[1];
$status=$row[2];
$time=$row[3];

  if ($number >= 5) {
  echo "<a href='userpages.phtml?username=$name'>$name</a> ($number)<br>\n";
  }
}


?>

<img src="<? echo URLBASE ?>/journals/img/no.gif" alt="" width="1" height="7" border="0"><br>

(<a href="roll_call_all.phtml">complete list</a>)<br>

<img src="<? echo URLBASE ?>/journals/img/no.gif" alt="" width="1" height="7" border="0"><br>
</p></td>

<!-- END PHP Dynamically Required File: rollcall.inc -->











