 

<!-- begin extra-special elly.inc, because few people are so cool. -->


<TABLE WIDTH="100%" BORDER="1" CELLSPACING="0" CELLPADDING="2" BORDERCOLOR="#333333">

<TR BGCOLOR="#999999">
<TD>
<CENTER><FONT SIZE="2" COLOR="#333333"><STRONG><TT>4(</TT><a href='http://elly.org'>elly</a><TT>)4</TT></STRONG></FONT>
</TD>
</TR>
<TR BGCOLOR="#DED3D3" ALIGN="left" VALIGN="top">
<TD>
<DIV ALIGN="left">
<P>

<!-- SELECT * FROM articles WHERE username='elly' and status='2' ORDER BY article_id DESC -->

<!-- this is a variant of the file "insert_articles.inc", b/c the engine is hot -->
<?

$result_set = mysql( "textocal", "SELECT * FROM pending_articles WHERE username='elly' OR username='le' AND status='2' ORDER BY time DESC" );

$url = "article.phtml?id=$d->article_id";

// multiple rows 
while ( $individual_row = mysql_fetch_object( $result_set ) ) {
   echo "<CENTER>";
   echo "<font face='arial' size='2'><a href=\"$url$individual_row->article_id.txt\"><B>$individual_row->title</a></B><BR>"; 
//   echo "by <a href='$individual_row->web' target='new'>$individual_row->username</a><br> ";
//   echo "$individual_row->blurb</font><br>";
   echo "<font face=\"arial\" size='1'>$individual_row->date</font><br> "; 
   echo "</CENTER>";
}


?>
<!-- end the elly select statement -->

</P>
</TD>
</TR>
</table>

<!-- include that final line break or the entire thing will be fucked. -->

<BR>

<!-- END PHP Dynamically Required File: elly.inc -->
 