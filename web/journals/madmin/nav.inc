<?
// $Id$

$page=split('/',$SCRIPT_NAME);
$last=end($page);

$url = array(
             "index.phtml" => "Home",
	     "users.phtml" => "Users",
             "comments.phtml" => "Comments",
             "articles.phtml" => "Articles"
	     );

foreach ($url as $key => $val) {
  if ($key!="$last") {
    $html = $html . <<<EOT
<TD BGCOLOR="#FFFFFF">
 <a href="./$key">$val</a>
</TD>
EOT;
  } elseif ($key==$last) {
$html = $html . <<<EOT
<TD BGCOLOR="#CCCCFF">
  $val
</TD>
EOT;
  }
}
echo <<<EOT
<TABLE ALIGN="CENTER">
  <TR>
    $html
  </TR>
</TABLE>
EOT;

//
// start the second levels
//

$article_sub=array(
		   "Info" => "article_info.phtml",
		   "Edit" => "edit_article.phtml",
		   "Preview" => "preview_article.phtml",
		   "Categoize" => "categorize_article.phtml",
		   "View Images" => "view_images.phtml",
		   "Add Image" => "submit_image.phtml",
		   "Status" => "status.phtml"
		   );

if (in_array("$last", $article_sub)) {
  foreach ($article_sub as $name => $url) {
    if ("$last"!="$url") {
      $into = "<TD><A HREF=\"$url?id=$id\">$name</a></TD>\n";
    } else {
      $into = "<TD  BGCOLOR=\"#CCCCFF\">$name</TD>\n";
    }
    if ($sub) $sub .= $into;
    if (!$sub) $sub = $into;      
  }
echo <<<EOT
<TABLE ALIGN="CENTER" BGCOLOR="#FFFFFF" BORDERCOLOR="red" BORDER=2 CELLSHADING=0 CELLSPACING=0>
<TR>
$sub
</TR>
</TABLE>
EOT;

}

?>
<BR><BR>
