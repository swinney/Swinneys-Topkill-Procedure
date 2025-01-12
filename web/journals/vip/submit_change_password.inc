<?
// $Id$
?>

<table cellpadding="2" cellspacing="0" border="0">
<tr>
<td colspan="2">
<form method="POST" action="process_change_password.php">
<span class="header">
<?

if ($error_msg) {
  echo "<b>$error_msg</b>";
}
else
{
  echo "<b>Change Password for $_SESSION['authenticated_username']:</b>";
}
?>
</span></td>
</tr>

<tr>
<td align="right">
<p>current password:</p></td>

<td align="left">
<input type="password" name="old_password" size="25" maxlength="20">
</td>
</tr>
<tr>
<td align="right">
<p>new password:</p>
</td>
<td align="left">
<input type="password" name="new_password1" size="25" maxlength="20">
</td>
</tr>
<tr>
<td align="right">
<p>new password (again):</p>
</td>
<td align="left">
<input type="password" name="new_password2" size="25" maxlength="20">
</td>
</tr>
<tr>
<td align="left">
&nbsp;
</td>
<td align="left">
<input type="submit" value="change it">
</td>
</tr>
</table>

</form>

