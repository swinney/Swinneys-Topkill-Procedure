<!-- begin login form-->
<?
// the first time the page is visited, save the location where the
// "log in" link was clicked so we can redirect back to it upon
// successful authentication
if (! session_is_registered("back_to")) {
  $back_to = $HTTP_REFERER;
  session_register("back_to");
}
?>

<form action="process_login.phtml" method="POST">
<table cellpadding="2" cellspacing="0" border="0">
<tr>
<td colspan="2">

<?
if ($error_msg) {
  session_unregister("error_msg");
  echo <<<EOT
<span class="header"><b>$error_msg</b></span>
EOT;
    }
else
    {
    echo '<span class="header"><b>'.$title.':</b></span>';
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
<td>&nbsp;</td>

<td>
<input type="submit" value="that's me"></td>
</tr>
</table>
</form>

<!-- end login form -->



