<?
#$Id$
require_once("global.inc");
?>

<!-- begin registration form-->

<table border="0" cellspacing="0" cellpadding="2">
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

<form action="process_register.phtml" method="POST">

<tr>
<td align="right">
<p>you are:</p></td>

<td>
<input type="text" name="username" size="25" maxlength="20"></td>
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
<p>email address:</p></td>

<td>
<p><input type="text" name="email" size="25" maxlength="40"></p></td>
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


