<?
// $Id$

?>

<FORM NAME="message" ACTION="process_message.phtml" METHOD="POST">
<TABLE WIDTH=600>
  <TR>
    <TD>
    </TD>
    <TD>
<SELECT NAME="to_user">
<option value="">*userlist*
<?
$query="SELECT user_id,username FROM user ORDER BY username";
$res=mysql_query($query);
while ($d=mysql_fetch_object($res)) {
  echo "<option value='$d->user_id'>$d->username\n";
}
?>
</SELECT>
    <a href="./add_alias.phtml">add alias</a>
    </TD>
  </TR>   
  <TR>
    <TD ALIGN="right" VALIGN="top">
To:
    </TD>
    <TD>
<INPUT NAME="to_user" TYPE="text" VALUE="" SIZE=10>
<INPUT TYPE=SUBMIT NAME=SUBMIT VALUE="send">
</TD>
</TR>

<TR>
<TD ALIGN="right" VALIGN="top">
Msg:
</TD>
<TD>
<TEXTAREA NAME="text" TYPE="text" COLS="20" ROWS="5"></TEXTAREA>
</TD>
</TR>
<TR>
<TD>
</TD>
<TD>
<INPUT TYPE="radio" NAME="send_type" VALUE="msg" CHECKED> msg
<INPUT TYPE="radio" NAME="send_type" VALUE="email"> email
</TD>
</TR>
</TABLE>
</FORM>