 


<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=0><TR BGCOLOR="#999999">
<TD>
<DIV ALIGN="center">
<FONT FACE="Verdana, Arial, Helvetica, sans-serif" SIZE="2">
<STRONG>
<FONT COLOR="#333333">Fine Print</FONT>
</STRONG>
</FONT>
</DIV>
</TD>
</TR>
<TR BGCOLOR="#DED3D3" ALIGN="left" VALIGN="top">
<TD>
<DIV ALIGN="left">
<P>
<FONT FACE="Verdana, Arial, Helvetica, sans-serif" SIZE="1" Color="#333333">



<?php 

include "../connect.inc";

$res = mysql("textocal","select * from fineprint order by unique_id desc limit 1 "); 

$d = mysql_fetch_object ( $res );

echo "<BR><B>date:</B><BR>\n";
echo "$d->date\n";
echo "<BR><BR><B>reading:</B>\n<BR>";
echo "$d->book\n"; 
echo "<BR><BR><B>wishing:</B><BR>\n"; 
echo "$d->wishing\n";
echo "<BR><BR><B>listening:</B><BR>\n";
echo "$d->listening\n"; 


?>



</FONT></P>
</DIV>
</TD>
</TR>
</TABLE>