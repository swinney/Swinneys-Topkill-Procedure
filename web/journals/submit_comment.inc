<?
// $Id$

require_once("./global.inc");


?>

<form action="process_comment.phtml" method=post enctype="multipart/form-data">
<input type="hidden" name="article_id" value="<? echo "$id"?>">

<table width="375" border="0" cellspacing="0" cellpadding="2">
<tr>
<td colspan="3">
<p class="header"><b><? echo $title ?></b>

<?
if (error_msg) {
  session_unregister("error_msg");
  echo <<<EOT
<br>
<b><span class="error">$error_msg</span></b>
EOT;
}
?>

</p></td>
</tr>

<tr>
<td align="right" COLSPAN=2><p>thus spake:
<input type="text" size="10" name="username" value="<? if ($authenticated_username) { echo "$authenticated_username"; } ?>">

 to
<SELECT NAME="to_user">
<option value="0">all
<?
$query="SELECT distinct(username), user_id FROM comments WHERE article_id=$id AND username NOT LIKE '%to%' ORDER BY username";
$res=mysql_query($query);
while ($d=mysql_fetch_object($res)) {
  if ($d->user_id) echo "<option value='$d->user_id'>$d->username\n";
}
?>
</SELECT>
</td><td></td>
</tr>
<tr>
<td></td>
<td>
</td>
<td></td>
</tr>
<tr>
<td colspan="2">
<p>comment:<br>
<textarea type=text name=comment cols=40 rows=20 wrap=virtual></textarea>
</p></td>

<td valign="top" NOWRAP>
<BR><BR>
<p>
<?

  $res = mysql_query ( "select * from nature order by nature_id asc");

  while ( $d = mysql_fetch_object($res) ) {
    echo "<input type='radio' name='nature' value='$d->nature_id'> $d->nature <br>";
  }

?>
<input type="submit" value="i said it">
</p></td>
</td>
</tr>

<tr>
<td colspan="3">
&nbsp;</td>
</tr>

<tr>
<td valign="top" align="right">

<!-- begin submit article categories -->

</td>
<td>
<p>please enclose your paragraphs in <tt>&lt;p&gt;...&lt;/p&gt;</tt> tags.  if you don't know what that means, then don't worry about it.</p>
</td>
<td valign="top">

</td>
</tr>
</table>
</form>




























