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
<P><A HREF="<? echo URLBASE ?>/index.php">swinney.org</A><BR>
<?
if ($_SESSION['authenticated_username']) {
  echo ' <A HREF="'.URLBASE.'/journals/vip/index.php">VIP</A><BR>'."\n";
} else {
  echo ' <A HREF="'.URLBASE.'/journals/login.php">log in</A><BR>'."\n";
}


$url = array (
   "entries.php"			=> "entries",
   "vip_edit_comments.php"		=> "comments",
   "submit_change_password.php"	=> "passwd",
   "submit_bozo.php"                  => "bozo",
);

foreach ($url as $path => $ref) {
   echo "<A HREF=\"$path\">$ref</A><BR>";  
}

if ($_SESSION['authenticated_username']) {
  echo ' <A HREF="'.URLBASE.'/journals/process_logout.php">log out</A><BR>';
  echo "\n";
}
?>
</P>
</TD>
</TR>
</TABLE>
<BR>
