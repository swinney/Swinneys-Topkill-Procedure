<?
// $Id$
?>

<table cellpadding="2" cellspacing="0" border="0" width="375">
<tr>
<td>
<p>
<?
if ($error_msg) {
  session_unregister("error_msg");
  echo <<<EOT
<span class="header"><b>$error_msg</b></span>
EOT;
}
elseif ($success_msg) {
  session_unregister("success_msg");
  echo <<<EOT
<span class="header"><b>$success_msg</b></span>
EOT;
}
else
{
  echo <<<EOT
<span class="header"><b>$title</b></span>
EOT;
}
?>

<form method="POST" action="process_bozo.phtml">
<?

if ($bozo_set) {

  echo <<<EOT
  
<br>

<table cellpadding="2" cellspacing="0" border="0" width="375">
<tr>
<td>
<p>
If forgiveness is on order, select one or more usernames below and
remove them from the list.
</p></td>
</tr>
</table>

<br>

<table cellpadding="2" cellspacing="0" border="0">
<tr>
<td align="right" valign="top">
<p>username:</p>
</td>
<td align="left">
<select name="username[]" size="5" multiple>

EOT;

$query = "SELECT bozo_id,bozoname FROM user_bozo WHERE user_id=$authenticated_user_id";
$res = mysql_query($query) or die($query);
while ($d=mysql_fetch_object($res)) {
    echo <<<EOT
<option value=$d->bozo_id> $d->bozoname
EOT;
  }

  echo <<<EOT
</select>
</td>
</tr>
<tr>
<td align="left" valign="middle">
&nbsp;
</td>
<td align="left" valign="middle">
<input type="submit" name="remove" value="remove bozo(s)">
</td>
</tr>
</table>

EOT;
}
?>
</table>
</form>
