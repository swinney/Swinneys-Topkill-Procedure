







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

<!-- WHAT IS GOING ON IN THE WORLD...  WHO?  -->

<?

include "connect.inc";

$res = mysql ("swinney", "SELECT DISTINCT username FROM pending_articles WHERE status='2' OR status='3' ORDER BY username");

while ($row = mysql_fetch_object ($res)) {
  echo "<a href='userpages.phtml?username=$row->username'>$row->username</a><br>";
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











