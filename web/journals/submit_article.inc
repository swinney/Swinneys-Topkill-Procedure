<PRE>$Id$</PRE>
<?
// include the top with the global include 
include "templates/top.inc";

echo "<form action=\"submit_article.phtml?page=1\" method=post>";
echo "<TABLE WIDTH=400 BORDER=0 CELLSPACING=0 CELLPADDING=0>";


echo "<TR><TD COLSPAN=2>page: $page</TD>";
echo "<TR>";
echo "<TD>Name</TD>";
echo "<TD ALIGN=\"right\">";



if ($page==1) 

{
	echo "<TT>ck</TT><INPUT TYPE=TEXT NAME=username VALUE=$username SIZE=30 maxlength=50>";

}

	else

{

	echo "<INPUT TYPE=TEXT NAME=username SIZE=30 maxlength=50>";

}

echo "</TD>";
echo "</TR>";

echo "<TR>";
echo "<TD>Website or email</TD>";
echo "<TD ALIGN=\"right\">\n";

if ($page==1)

{

	echo "<TT>ck</TT><INPUT TYPE=TEXT NAME=web VALUE=$web SIZE=30 maxlength=50>\n";

}

	else

{
	echo "<INPUT TYPE=TEXT NAME=web SIZE=30 maxlength=50>\n";

}

echo "</TD>";
echo "</TR>";

echo "<TR>";
echo "<TD>";
echo "<P>Title</P>";
echo "</TD>";
echo "<TD ALIGN=\"right\">";

if ($page==1)

{

	echo "<TT>ck</TT><INPUT TYPE=text NAME=title VALUE=$title SIZE=30 maxlength=50>";

}

	else

{

        echo "<INPUT TYPE=text NAME=title SIZE=30 maxlength=50>";

}

echo "</TD>";
echo "</TR>";

echo "<TR>";
echo "<TD>";
echo "<P>Blurb</P>";
echo "</TD>";
echo "<TD ALIGN=\"right\">";

if ($page==1)

{       
        
	echo "<TT>ck</TT><INPUT TYPE=text NAME=blurb VALUE=$blurb SIZE=30 maxlength=255>";


}       
        
        else

{       
        
	echo "<INPUT TYPE=text NAME=blurb SIZE=30 maxlength=255>";


}



echo "</TD>";
echo "</TR>";


echo "<TR>";
echo "<TD ALIGN=\"left\">";
echo "<P>Keywords (delimited by commas)</P>";
echo "</TD>";
echo "<TD ALIGN=\"right\">";


if ($page==1)

{       

echo "<TT>ck</TT><INPUT TYPE=text NAME=keywords VALUE=$keywords SIZE=30 maxlength=100>";

}       
        
        else

{     
  
echo "<INPUT TYPE=text NAME=keywords SIZE=30 maxlength=100>";        

}



echo "</TD>";
echo "</TR>";


echo "

<TR>
<TD COLSPAN=2>
<P>Please enclose your paragraphs in <TT>&lt;P&gt;...&lt;/P&gt;</TT> tags.  If you don't know what that means, then don't worry about it.</P>

<TEXTAREA TYPE=text  NAME=content COLS=50 ROWS=20 wrap=virtual></TEXTAREA>
</TD>
</TR>
</TABLE>


<P>What category best describes you?</P>

";


  
$res = mysql_query ( "SELECT * FROM categories ORDER BY name ASC");
$index=0;




echo "<TABLE><TR>";

while ( $d = mysql_fetch_object($res) ) 

{

	$index++;
	$remainder = $index % 3;

	echo "<TD><input type='checkbox' name='cat$d->category_id'> $d->name </TD>";

	if($remainder==0)

	{

		echo "</TR><TR>";

	}


}

echo "</TR></TABLE>";
?>

<INPUT TYPE="SUBMIT">   <INPUT TYPE="RESET">

</form>
</BODY>
</HTML>

<?

# end loop one with increment of page
$page=1;


?>
















