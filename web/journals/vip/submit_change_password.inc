<?
// $Id$
if ($error_msg) {
  echo <<<EOT
<p>
<b><font color="red">$error_msg</font></b>
</p>
EOT;
}

if ($success_msg) {
  echo <<<EOT
<p>
<b><font color="green">$success_msg</font></b>
</p>
EOT;
}
?>
<p>
Change your password:
</p>

<form method="POST" action="process_change_password.phtml">

<table>
<tr>
<td align="right" valign="middle">
<p>old password:</p>
</td>
<td align="left" valign="middle">
<input type="password" name="old_password" size="10" maxlength="20">
</td>
</tr>
<tr>
<td align="right" valign="middle">
<p>new password:</p>
</td>
<td align="left" valign="middle">
<input type="password" name="new_password1" size="10" maxlength="20">
</td>
</tr>
<tr>
<td align="right" valign="middle">
<p>new password (again):</p>
</td>
<td align="left" valign="middle">
<input type="password" name="new_password2" size="10" maxlength="20">
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

