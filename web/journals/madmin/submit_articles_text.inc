<?
//////////////////////////////////////////////////
// $Id$
// 
// register aid for the admin processing, 
// be sure to destroy it though or it will
// mess everything up later when pages try
// to call aid.
//
// this session register is NECESSARY!
// session_register("id");
require_once("../global.inc");
include_once("./top.inc");
include_once("./nav.inc");

if (isset($id)) {

    $query="SELECT articles_text.text,
                   articles_info.title,
                   articles_info.blurb 
            FROM articles_text, 
                 articles_info 
            WHERE articles_text.article_id=articles_info.article_id 
            AND articles_info.article_id=$id";

    $res=mysql_query($query) or die (error_page($query));
    while ($d=mysql_fetch_object($res)) {
        $title=stripslashes($d->title);
        $blurb=stripslashes($d->blurb);
        $text=stripslashes($d->text);
    }

echo <<<EOT
<a href="../article.phtml?id=$id" target="new">Preview Page</a>
<FORM NAME="edit" ACTION="process_articles_text.phtml" METHOD="post">
<TABLE BORDER=0>
<TR><TD>Title: </TD>
<TD ALIGN="RIGHT"><INPUT TYPE="text" NAME="title" VALUE="$title" SIZE=80>
</TD></TR>
<TR><TD>Blurb: </TD>
<TD ALIGN="RIGHT"><INPUT TYPE="text" NAME="blurb" VALUE="$blurb" SIZE=80>
</TD></TR>
<TR><TD COLSPAN=2>
<TEXTAREA NAME="text" COLS=90 rows=25 wrap=virtual>$text</TEXTAREA>
</TD></TR>
<TR><TD COLSPAN=2>
<INPUT TYPE="SUBMIT" NAME="submit" VALUE="update">
<INPUT TYPE="SUBMIT" NAME="submit" VALUE="preview">
</TABLE>
</FORM>
EOT;

}

//
// if $id is not set and this is a new article then
//
if (!isset($id)) {
echo <<<EOT
<FORM NAME="edit" ACTION="process_articles_text.php" METHOD="post">
<TABLE BORDER=0>
<TR><TD>Title: </TD>
<TD ALIGN="RIGHT"><INPUT TYPE="text" NAME="title" SIZE=80>
</TD></TR>
<TR><TD COLSPAN=2>
<TEXTAREA NAME="text" COLS=90 rows=15 wrap=virtual></TEXTAREA>
</TD></TR>
<TR><TD COLSPAN=2>
<INPUT TYPE="SUBMIT" NAME="submit" VALUE="update">
<INPUT TYPE="SUBMIT" NAME="submit" VALUE="preview">
</TABLE>
</FORM>
EOT;



//
// end loop for top level process
//
}
?>


