<!--
$Id$
##################################
# if only you knew the comments that
# were in the php code.  you would
# fear.  fear. lucky you i have morals
# i wont just let them show up in the
# html where my mother might read them.
# -OMS
-->
<?/*
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
*/?>

<!-- BEGIN PHP Dynamically Required File: rollcall.inc -->


<TABLE WIDTH="100%" BORDER="0" CELLSPACING="0" CELLPADDING="2" BORDERCOLOR="#333333">

<TR>
<TD>
<P>By Author<BR>
<a href="roll_call_all.phtml">big list</a></P>
</TD>
</TR>
<TR ALIGN="left" VALIGN="top">
<TD>
<DIV ALIGN="left">
<P><FONT FACE="Verdana, Arial, Helvetica, sans-serif" SIZE="2">

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
$res = mysql ("$DB", "SELECT DISTINCT username, count(username) AS number FROM pending_articles GROUP BY username");

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

  if ($number > 5) {
  echo "<a href='userpages.phtml?username=$name'>$name($number)</a><br>\n";
  }
}


?>

</FONT>
</P>
</TD>
</TR>
</table>

<!-- include that final line break or the entire thing will be fucked. -->

<BR>

<!-- END PHP Dynamically Required File: rollcall.inc -->











