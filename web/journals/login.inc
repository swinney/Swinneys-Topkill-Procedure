<!-- begin login form-->

<div align="center">
<?
if (error_msg) {
  session_unregister("error_msg");
  echo <<<EOT
<p>
<b><font color="red">$error_msg</font></b>
</p>
EOT;
}

// the first time the page is visited, save the location where the
// "log in" link was clicked so we can redirect back to it upon
// successful authentication
if (! session_is_registered("back_to")) {
  $back_to = $HTTP_REFERER;
  echo "registering back_to as $back_to<br>";
  session_register("back_to");
}

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



