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
?>
<form action="process_login.phtml" method="POST">
username:
<input type="text" name="username" size="10" maxlength="20"
  value="<? echo $username ?>">
<br>
password:
<input type="password" name="password" size="10" maxlength="20">
<br>
<input type="submit" value="that's me">
</form>
</div>

<!-- end login form -->
