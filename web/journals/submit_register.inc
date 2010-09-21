<?
// $Id$
?>


<!-- begin registration form-->

<form action="./process_register.phtml" method="POST">

<table border="0" cellspacing="0" cellpadding="2">
<tr>
<td colspan="2">

<?
if ($error_msg) {
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
<p>username (only letters,<BR> numbers, _ and -, must <BR>have at least 3 characters.):</p>
</td>

<td>
<input type="text" name="username" value="<?=$username?>" size="25" maxlength="20">
</td>
</tr>

<tr>
<td align="right">
<p>password:</p></td>

<td>
<p><input type="password" name="password" size="25" maxlength="20"></p></td>
</tr>

<tr>
<td align="right">
<p>confirm password:</p></td>

<td>
<p><input type="password" name="password2" size="25" maxlength="20"></p></td>
</tr>

<tr>
<td align="right">
<p>email address (optional):</p></td>

<td>
<p><input type="text" name="email" value="<?=$email?>" size="25" maxlength="40"></p></td>
</tr>
<tr>
<td colspan=2>
<? 

require_once('../recap/recaptchalib.php');

// Get a key from http://recaptcha.net/api/getkey
$publickey = "6Lc2XwkAAAAAAGEm9BljcoLg8us0scyuB0WmTnd_";
$privatekey = "6Lc2XwkAAAAAAJbXJrjQAK-hYqtFBAE4FW37wlPD";

# the response from reCAPTCHA
$resp = null;
# the error code from reCAPTCHA, if any
$error = null;

echo $recap_html = recaptcha_get_html($publickey, $error);

?>
</td>
</tr>

<tr>
<td>&nbsp;</td>

<td>
<input type="submit" value="register me"></td>
</tr>

</table>
</form>
</div>


<!-- end register form -->


