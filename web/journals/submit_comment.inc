<?
// $Id$

require_once("./global.inc");

?>

<form action="process_comment.phtml" method=post enctype="multipart/form-data">
<input type="hidden" name="article_id" value="<? echo "$article_id"?>">



<table width="375" border="0" cellspacing="0" cellpadding="2">
<tr>
<td colspan="3">
<span class="header"><b><? echo "$title"; ?></b></span>
</td>
</tr>

<tr>
<td align="right"><p>you are:</p></td>
<td>
 <input type="text" name="username" size="25" maxlength="30" value="<?=$authenticated_username?>">
</td>

<td>
&nbsp;</td>
</tr>

<tr>
<td colspan="3">
&nbsp;</td>
</tr>

<tr>
<td colspan="2">
<p>comment:<br>
<textarea type=text name=comment cols=50 rows=20 wrap=virtual></textarea>
</p></td>

<td valign="top">
<p>&nbsp;<br>please enclose your paragraphs in <tt>&lt;p&gt;...&lt;/p&gt;</tt> tags.  if you don't know what that means, then don't worry about it.</p></td>
</tr>

<tr>
<td colspan="3">
&nbsp;</td>
</tr>

<tr>
<td valign="top" align="right">

<!-- begin submit article categories -->

<p>what category best describes you?</p>
</td>
<td><p>
<?

  $res = mysql_query ( "select * from nature order by nature_id asc");

  while ( $d = mysql_fetch_object($res) ) {
    echo "<input type='radio' name='nature' value='$d->nature_id'> $d->nature <br>";
  }

?></p></td>
<td valign="top"><input type="submit" value="i said it"></td>
</tr>
</table>
</form>
