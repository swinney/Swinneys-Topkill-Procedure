<?
// $Id$ 
if (count($sess_lang) > 1) {
  $opt_lang =<<<EOT
<SELECT NAME="language">
EOT;

 foreach($sess_lang as $lang) {
   if ($lang != $last_lang) {
     $opt_lang .= "<OPTION VALUE='$lang'>$lang\n";
   } else {
     $opt_lang .= "<OPTION VALUE='$lang' SELECTED>$lang\n";     
   }
 }
 $opt_lang .="</SELECT>\n";
}

?>
<tr>
<td>
<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td>
<img src="journals/img/name.gif" alt="name:" width="40" height="17" border="0"></td>

<td>
&nbsp;</td>

<td>
<img src="journals/img/thought.gif" alt="thought:" width="53" height="17" border="0"></td>

<td>
<form name="ithoughtitform" action="journals/process_thought.php" method="POST" enctype="multipart/form-data" >
&nbsp;</td>
</tr>
<?
if (count($sess_lang)==1) {
  echo "<INPUT TYPE=HIDDEN NAME=language VALUE='$sess_lang[0]'>\n";
}
?>
<tr>
<td>
<input type="text" size="10" name="username" value="<? if ($_SESSION['authenticated_username']) { echo "$_SESSION['authenticated_username']"; } ?>"></td>

<td>
&nbsp;</td>

<td>
<input type="text" name="thought"><? echo $opt_lang;?></td>

<td valign="center">&nbsp;
<input type=submit value="I Thought It">
<sup><a href="chat/index.php">(chat)</a></sup></td>
</form></tr>
</table></td>
</tr>
