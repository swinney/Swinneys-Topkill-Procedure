<? 
#  $Id$

require_once("global.inc");
include "templates/top.inc";
include "templates/swinney.req";
if ($rollcall==1) {
  include "templates/rollcall.inc";
} else {
  include "templates/norollcall.inc";
}
include "templates/endleft.inc";

include "$into_template";

if (isset($into_template2)) {
  include "$into_template2";
}

if (basename($PHP_SELF)=="article.phtml") {
  $query = "SELECT article_id,title,blurb FROM articles_info WHERE user_id=124";
  $res = $db->query($query);
  while ($row = $res->fetchRow()) {
    $blurb=":<BR> ". $row[2];
    $html .= "<P><A HREF=\"./article.phtml?id=$row[0]\"><B>$row[1]</B></A>$blurb</P>\n";
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


include "templates/bottom.req";
include "templates/footer.inc";
?>


