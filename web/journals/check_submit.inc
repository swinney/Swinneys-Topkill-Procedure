<?
#$Id$
?>
<form action='submit_article.phtml' method=post>
<TABLE WIDTH=400 BORDER=0 CELLSPACING=0 CELLPADDING=0>

<TR>

    <TD>Name</TD>
    <TD ALIGN='right'>
    <? echo "$username"; ?><BR>
    <INPUT TYPE=TEXT NAME=username SIZE=30 maxlength=50>
    </TD>
    </TR>

    <TR>
    <TD>Website or email</TD>
    <TD ALIGN='right'>
    <? echo "$web"; ?><BR>
    <INPUT TYPE=TEXT NAME=web SIZE=30 maxlength=50>
    </TD>
    </TR>

    <TR>
    <TD>
    <P>Title</P>
    </TD>
    <TD ALIGN="right">
    <? echo "$title"; ?><BR>
    <INPUT TYPE=text NAME=title SIZE=30 maxlength=50>
    </TD>
    </TR>

    <TR>
    <TD>
    <P>Blurb</P>
    </TD>
    <TD ALIGN="right">
    <? echo "$blurb"; ?><BR>
    <INPUT TYPE=text NAME=blurb VALUE="<? echo "$blurb"; ?>"SIZE=30 maxlength=255>
    </TD>
    </TR>


    <TR>
    <TD ALIGN="left">
    <P>Keywords (delimited by commas)</P>
    </TD>
    <TD ALIGN="right">
    <? echo "$keywords"; ?>
    <INPUT TYPE=text NAME=keywords VALUE="<? echo "$keywords"; ?>"SIZE=30 maxlength=100>
    </TD>
    </TR>


    <TR>
    <TD COLSPAN=2>
    <P>Please enclose your paragraphs in <TT>&lt;P&gt;...&lt;/P&gt;</TT> tags.  If you don't know what that means, then don't worry about it.</P>
    <? echo "$content"; ?><BR>
    <TEXTAREA TYPE=text  NAME=content COLS=50 ROWS=20 wrap=virtual><? echo "$content"; ?></TEXTAREA>
    </TD>
    </TR>
    </TABLE>


    <P>What category best describes you?</P>

    <?

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

    <INPUT TYPE="SUBMIT" NAME="PAGE" VALUE=3>   
    <INPUT TYPE="SUBMIT" NAME="PREVIEW" VALUE=666>
    <INPUT TYPE="RESET">

    </form>
    </BODY>
    </HTML>







