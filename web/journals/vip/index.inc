
<p>
<b>Hi <? echo $authenticated_username; ?>!</b>
Your call is very important to us.
</p>

<?
if ($error_msg) {
  echo <<<EOT
<p>
<b><font color="red">$error_msg</font></b>
</p>
EOT;
}
?>

<hr>

<p>
Change your password:
</p>

<form method="POST" action="process_change_password.phtml">

<table>
<tr>
<td align="right" valign="middle">
<p>password:</p>
</td>
<td align="left" valign="middle">
<input type="password" name="password1" size="10" maxlength="20">
</td>
</tr>
<tr>
<td align="right" valign="middle">
<p>confirm:</p>
</td>
<td align="left" valign="middle">
<input type="password" name="password2" size="10" maxlength="20">
</td>
</tr>
<tr>
<td align="left" valign="middle">
&nbsp;
</td>
<td align="left" valign="middle">
<input type="submit" value="do it">
</td>
</tr>
</table>

</form>

