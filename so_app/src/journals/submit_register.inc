<?
// $Id$
?>


<!-- begin registration form-->

<form action="process_register.php" method="POST">

<table border="0" cellspacing="0" cellpadding="2">
<tr>
<td colspan="2">

<?
if (isset($error_msg)) {
  session_unregister("error_msg");
  echo <<<EOT
<span class="header"><b>$error_msg</b></span>
EOT;
} else {
  echo '<span class="header"><b>', $title, ':</b></span>';
}
?></td>
</tr>
<tr>
<td align="right">
<p>username:</p>
</td>

<td>
<input type="text" name="username" placeholder="Username" required>
</td>
</tr>

<tr>
<td align="right">
<p>password:</p></td>

<td>
<p><input type="password" name="password" placeholder="Password" required></p></td>
</tr>
<tr>
<td align="right">
<p>email address</p></td>

<td>
<p><input type="email" name="email" placeholder="Email" required></p></td>
</tr>
<tr>
<td colspan=2>
<form action="process_register.php" method="POST">
    <div class="g-recaptcha" data-sitekey="your-site-key"></div>
</form>

</td>
</tr>

<tr>
<td>&nbsp;</td>

<td>
    <input type="submit" value="Register">
</td>
</tr>

</table>
</form>
</div>


<!-- end register form -->


