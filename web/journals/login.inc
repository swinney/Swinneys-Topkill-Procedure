<?
// the first time the page is visited, save the location where the
// "log in" link was clicked so we can redirect back to it upon
// successful authentication
$error_msg.=<<<EOT
<P><B>Please log in first:</B></P>
EOT;
if (!$back_to) {
  session_register("back_to");
  $back_to="$HTTP_REFERER";
}
?>
<!-- begin login form-->
<form action="./process_login.phtml" method="POST">
<input type=hidden name=back_to value="<?=urldecode($back_to);?>">
<table cellpadding="2" cellspacing="0" border="0">
<tr>
<td colspan="2">
<?
if ($back_to) {
  session_unregister("error_msg");
  echo <<<EOT
<span class="header"><b>$error_msg</b></span>
EOT;
} else {
  echo '<span class="header"><b>', $title, ': </b></span>';
  $back_to = URLBASE;
}
?></td>
</tr>

<tr>
<td align="right">
<p>you are: </p></td>

<td>
<input type="text" name="username" size="25" maxlength="20"
  value="<? echo $username ?>"></td>
</tr>

<tr>
<td align="right">
<p>password: </p></td>

<td>
<p><input type="password" name="password" size="25" maxlength="20"></p></td>
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
<input type="submit" value="that's me">
</td></tr>
<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
</tr>
<tr>
<?php 
#if ($back_to) {
#  echo "<TD><P><B>You arrived from:</B></TD>"; 
#  echo "<TD><a href='$back_to'>$back_to</a></P></TD>";
#}
?>
</tr>
</table>
</form>
<!-- end login form -->
