<!-- begin login form-->

<div align="center">
<?
if ($login_error_msg) {
  echo <<<EOT
<p>
<b><font color="red">$login_error_msg</font></b>
</p>
EOT;
}

$back_to = $HTTP_REFERER;
session_register("back_to");

?>
<TABLE><TR><TD>
<form action="process_login.phtml" method="POST">
<P>username:</P>
</TD><TD>
<input type="text" name="username" size="10" maxlength="20"
  value="<? echo $username ?>">
</TD></TR>
<TR><TD>
<P>password:</P>
</TD><TD>
<P><input type="password" name="password" size="10" maxlength="20"></P>
</TD></TR>
<TR><TD></TD><TD>
<input type="submit" value="that's me">
</form>
</div>
</TD></TR></TABLE>
<!-- end login form -->



