







<!-- BEGIN PHP Dynamically Required File: rollcall.inc -->


<TABLE WIDTH="100%" BORDER="1" CELLSPACING="0" CELLPADDING="2" BORDERCOLOR="#333333">

<TR BGCOLOR="#999999">
<TD>
<CENTER><FONT FACE="Verdana, Arial, Helvetica, sans-serif"
SIZE="2"><STRONG><FONT
COLOR="#333333">By Author</FONT></STRONG></FONT></CENTER> </TD>
</TR>
<TR BGCOLOR="#DED3D3" ALIGN="left" VALIGN="top">
<TD>
<DIV ALIGN="left">
<P><FONT FACE="Verdana, Arial, Helvetica, sans-serif" SIZE="2">

<A HREF="roll_call_all.phtml">complete list</A><BR>
<TT>--------</TT><BR>
<!-- WHAT IS GOING ON IN THE WORLD...  WHO?  -->

<?

include "connect.inc";

$res = mysql ("$DB", "SELECT DISTINCT username FROM pending_articles WHERE status='2' OR status='3' ORDER BY username");



while ($row = mysql_fetch_object ($res)) {
  $res2 = mysql ("$DB", "SELECT count(*) FROM pending_articles WHERE username='$row->username'");
  $res3 = mysql ("$DB", "SELECT count(*) FROM comments WHERE username='$row->username'");
  
  $count2 = mysql_fetch_row($res2);
  $count3 = mysql_fetch_row($res3);
  if ($count2[0] > 5) {
  echo "<a href='userpages.phtml?username=$row->username'>$row->username($count2[0]|$count3[0])</a><br>";
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











