<?
// $Id$
?>

<table width=375 border="0" cellspacing="0" cellpadding="2">
<tr>
<td nowrap colspan="3">

<p class="header"><b><? echo $title ?></b><FONT="GREEN"><? 
if ($authenticated_user_id) { 
  echo ': <FONT COLOR="GREEN">You are logged in.</FONT>';
} else {
  echo ': <FONT COLOR="RED">Warning, you are NOT logged in.</FONT>';
}
//
// temp_aid is set if user just came from the VIP area
//
if ($temp_aid) {
  echo <<<EOT
  (<a href="../article.phtml?id=$temp_aid" target="new">preview</a>)</P>
EOT;
}

if ($error_msg) {
  session_unregister("error_msg");
  echo <<<EOT
<br>
<b><span class="error">ERROR MESSAGE:<BR>$error_msg</span></b>
EOT;
}
?>
</p></td>
</tr>


<form action="process_article.phtml" method="POST" name="isaiditform" ENCTYPE="multipart/form-data">

<tr>
<td align="right" nowrap>
<p>you are: </p></td>
<td>
<input type=text name=username size=25 maxlength=50  value="<?=$authenticated_username?>">
</td>
<td>&nbsp;</td>
</tr>

<tr>
<td align="right" nowrap>
<p>web or email address: </p></td>
<td>
<input type=text name=web value="<?=$web?>" size=25 maxlength=50>
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
<input type=text name=title value="<?=$temp_title?>" size=25 maxlength=50>
</td>
<td>&nbsp;</td>
</tr>

<tr>
<td align="right" nowrap>
<p>blurb: </p>
</td>
<td>
<input type=text name=blurb value="<?=$blurb?>" size=25 maxlength=255>
</td>
<td>&nbsp;</td>
</tr>

<tr>
<td align="right" nowrap>
<p>keywords: </p>
</td>
<td>
<input type=text name=keywords value="<?=$keywords?>" size=25 maxlength=100>
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
&nbsp;<input type="radio" name="images_too" value="no" checked>no
</p></td>
<td>&nbsp;</td>
</tr>
<tr>
<td align="right" nowrap>
<p>upload a text file: </P>
</td>
<td>
<INPUT TYPE="file" NAME="userfile" ACCEPT="filetype/html" SIZE=25 MAXLENTH=250>
</td>
</tr>
<tr>
<td align="center" nowrap colspan="2">
&nbsp;- or -</td>
</tr>

<tr>
<td colspan="2">
<p>body:<br>
<textarea type=text  name=content cols=50 rows=20 wrap=virtual><?=$text?></textarea></p></td>

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

if (isset($category)) {
  $query=<<<EOT
  SELECT name, 
         level1, 
         level1 & $category as sexy 
    FROM categories 
   WHERE name<>'' 
ORDER BY name ASC
EOT;

} else {
  $query=<<<EOT
  SELECT * 
    FROM categories 
ORDER BY name ASC
EOT;
}
  
$res = mysql_query($query);

# for the next loop, index
$i=0;

while ($d=mysql_fetch_object($res)) {

    echo "<input type='checkbox' name='cat[$i]' value='$d->level1'";
    if ($d->sexy!=0) {
      echo " CHECKED";
    }
    echo "> $d->name <br>\n";
    $i++;
} # child loop

?>
</p></td>
<td valign="top">
<?

$page=split('/',$SCRIPT_NAME);
$last=end($page);


if ($last=="edit_article.phtml") {
  $subval="update it";
} else {
  $subval="i said it";
}
?>

<input type=submit NAME="submit" value="<?=$subval?>">
</td>
</tr>
</table>
</form>
