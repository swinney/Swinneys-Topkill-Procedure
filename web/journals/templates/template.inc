<? 
#  $Id$

include (INCDIR ."/top.inc");
include (INCDIR ."/swinney.req");
if ($rollcall==1) {
  include (INCDIR ."/rollcall.inc");
} else {
  include (INCDIR ."/norollcall.inc");
}
include (INCDIR ."/endleft.inc");

include "$into_template";

if (isset($into_template2)) {
  include "$into_template2";
}

if (basename($PHP_SELF)=="article.phtml") {
  if ($author_id) {
    //  $query = "SELECT article_id,title,blurb FROM articles_info WHERE user_id=124";
    $query = "SELECT multi_info.multi_id,multi_info.title FROM multi_info WHERE user_id=$author_id";
    $res = $db->query($query);
    while ($row = $res->fetchRow()) {
      $blurb=":<BR> ". $row[2];
      $html .= "<P><A HREF=\"./index_multi.phtml?id=$row[0]\"><B>$row[1]</B></A>$blurb</P>\n";
    }
  

echo <<<EOT
<!-- Right Margin Matter Box -->
</TD>
<td width="33">
<img src="http://swinney.org/dev/journals/img/no.gif" alt="" width="33" height="1" border="0"></td>

<TD WIDTH="150" ALIGN=LEFT VALIGN=TOP>
<IMG SRC="img/rollcall.gif">
$html
</TD>
EOT;
  }
}

include (INCDIR ."/bottom.req");
include (INCDIR ."/footer.inc");
?>


