<?
#$Id$
if ($error_msg) {
  session_unregister("error_msg");
  echo <<<EOT
<p>
<b><font color="red">$error_msg</font></b>
</p>
EOT;
}

if ($success_msg) {
  session_unregister("success_msg");
  echo <<<EOT
<p>
<b><font color="green">$success_msg</font></b>
</p>
EOT;
}
?>

<form method="POST" action="process_bozo.phtml">

<p>
Somebody is a clown? Dont want to see what they have to say? Add them
to your bozo list below, and their articles and comments will be
filtered from your view of the site.
</p>

<table>
<tr>
<td align="right" valign="middle">
<p>username:</p>
</td>
<td align="left" valign="middle">
<input type="text" name="username" size="20" maxlength="20">
</td>
</tr>
<tr>
<td align="left" valign="middle">
&nbsp;
</td>
<td align="left" valign="middle">
<input type="submit" name="add" value="add bozo">
</td>
</tr>
</table>

<?
$num_bozos = count($bozos);
if ($num_bozos) {

  echo <<<EOT
<p>
Or, if forgiveness is on order, select one or more names below and
remove them from the list.
</p>

<table>
<tr>
<td align="right" valign="middle">
<p>username:</p>
</td>
<td align="left" valign="middle">
<select name="username[]" size="$num_bozos" multiple>

EOT;

  sort($bozos);
  foreach($bozos as $bozo) {
    echo <<<EOT
<option> $bozo
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

</form>
