<?
// $Id$
?>

<table width=375 border="0" cellspacing="0" cellpadding="2">
<tr>
<td nowrap colspan="3">
<p class="header"><b><? echo $title ?></b></p></td>
</tr>

<form action="process_article.phtml" method="POST" name="isaiditform">

<tr>
<td align="right" nowrap>
<p>you are: </p></td>
<td>
<input type=text name=username size=25 maxlength=50  value="<? if ($authenticated_username) { echo "$authenticated_username"; } ?>">
</td>
<td>&nbsp;</td>
</tr>

<tr>
<td align="right" nowrap>
<p>web or email address: </p></td>
<td>
<input type=text name=web size=25 maxlength=50>
</td>
<td>&nbsp;</td>
</tr>

<tr>
<td nowrap colspan="3">
&nbsp;</td>
</tr>

<tr>
<td align="right" nowrap>
<p>title: </p>
</td>
<td>
<input type=text name=title size=25 maxlength=50>
</td>
<td>&nbsp;</td>
</tr>

<tr>
<td align="right" nowrap>
<p>blurb: </p>
</td>
<td>
<input type=text name=blurb size=25 maxlength=255>
</td>
<td>&nbsp;</td>
</tr>

<tr>
<td align="right" nowrap>
<p>keywords: </p>
</td>
<td>
<input type=text name=keywords size=25 maxlength=100>
</td>

<td nowrap><p>(separated by commas)</p></td>
</tr>

<tr>
<td align="right" nowrap>
<p>got images? </p>
</td>
<td>
<p>  
<input type="radio" name="images_too" value="yes">yes
&nbsp;<input type="radio" name="images_too" value="no" checked>no</p></td>
<td>&nbsp;</td>
</tr>

<tr>
<td nowrap colspan="3">
&nbsp;</td>
</tr>

<tr>
<td colspan="2">
<p>body:<br>
<textarea type=text  name=content cols=50 rows=20 wrap=virtual></textarea></p></td>

<td valign="top">
<p>&nbsp;<br>please enclose your paragraphs in <tt>&lt;p&gt;...&lt;/p&gt;</tt> tags.  if you don't know what that means, then don't worry about it.</p></td>
</tr>

<tr>
<td nowrap colspan="3">
&nbsp;</td>
</tr>

<tr>
<td align="right" valign="top">
<p>what category best describes you?</p>
</td>
<td>
<p>
<?
  
$res = mysql_query("SELECT * FROM categories ORDER BY name ASC");

# for the next loop, index
$index=1;

while ($d=mysql_fetch_object($res)) {

echo "<input type='radio' name='category' value='cat$d->category_id'> $d->name <br>";

} # child loop

?>
</p></td>
<td valign="top"><input type=submit value="i said it"></td>
</tr>
</table>
</form>











