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

<br>
Is someone a clown? Don't want to see what they have to say? Add them
to your bozolist and their articles and comments will be filtered from your view of the site.
</p>
</td>
</tr>
</table>

<form method="POST" action="process_bozo.phtml">

<table cellpadding="2" cellspacing="0" border="0">
<tr>
<td align="right">
<p>username:</p></td>
<td align="left">
<input type="text" name="username" size="20" maxlength="20">
</td>
</tr>
<tr>
<td align="left">
&nbsp;
</td>
<td align="left">
<input type="submit" name="add" value="add bozo">
</td>
</tr>
</table>

<?
$num_bozos = count($bozos);
if ($num_bozos) {

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
