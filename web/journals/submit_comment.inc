
<form action="process_comment.phtml" method=post enctype="multipart/form-data">
<input type="hidden" name="article_id" value="<? echo "$article_id"?>">

<TABLE BORDER="0" CELLSPACING="0" CELLPADDING="5">
<TR>
<TD valign="top"><p><b>name:</b></p></td>
<td>
 <INPUT TYPE="text" NAME="username" SIZE="15" maxlength="30" wrap=hard>
</TD>
</TR>

<TR>
<TD valign="top">
<p><b>comment:</b><br>
(html ok)</p>
</td>
<td>
<TEXTAREA TYPE=text  NAME=comment COLS=60 ROWS=17 wrap=hard></TEXTAREA>
</TD>
</TR>
<tr>
<td valign="top">

<!-- BEGIN SUBMIT ARTICLE CATEGORIES -->

<p><b>what category <br>best describes you?</b></p>
</td>
<td><p>
<?
  include "connect.phtml";
  $res = mysql("$DB", "SELECT * FROM nature ORDER BY nature_id ASC");

  while ( $d = mysql_fetch_object($res) ) {
    echo "<input type='radio' name='nature' value='$d->nature_id'> $d->nature <br>";
  }

?>
<br><br>
<INPUT TYPE="SUBMIT" VALUE="I said it">   <INPUT TYPE="RESET" VALUE="reset">
</p>
</td>
</tr>
</table>
</form>






