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
?>

