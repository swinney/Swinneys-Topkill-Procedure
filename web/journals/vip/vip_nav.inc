<!-- BEGIN PHP Dynamically Required Page : swinney.req  -->




<TABLE WIDTH="500" BORDER="0" CELLSPACING="0" CELLPADDING="0" align=center>
<TR>
<TD>
<TABLE WIDTH="100%" CELLSPACING="0" CELLPADDING="10" BORDER="0" valign="top">
<tr>
<td valign=top width=20>
<TABLE BORDER=0 WIDTH="100%" CELLPADDING="0" CELLSPACING="0">
<TR ALIGN="left" VALIGN="top">
<TD valign="top">
<TABLE BORDER=0 CELLSPACING="0" CELLPADDING="2" WIDTH="100%" valign="top">
<TR ALIGN="left" VALIGN="top">
<TD>
<P><A HREF="<? echo URLBASE ?>/index.phtml">swinney.org</A><BR>
<?
if ($authenticated_username) {
  echo ' <A HREF="'.URLBASE.'/journals/vip/index.phtml">VIP</A><BR>'."\n";
} else {
  echo ' <A HREF="'.URLBASE.'/journals/login.phtml">log in</A><BR>'."\n";
}


$url = array (
   "entries.phtml"		=> "entries",
   "vip_edit_comments.phtml"	=> "comments",
   "chage_password.phtml" 	=> "passwd"
);

foreach ($url as $path => $ref) {
   echo "<A HREF=\"$path\">$ref</A><BR>";  
}

if ($authenticated_username) {
  echo ' <A HREF="'.URLBASE.'/journals/process_logout.phtml">log out</A><BR>';
  echo "\n";
}
?>
</P>
</TD>
</TR>
</TABLE>
<BR>

<!-- END PHP Dynamically Required Page: swinney.req -->


