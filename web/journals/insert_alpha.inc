<?
// $Id$

$alpha=array(1 => "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z");


if ($i) {
  $query=<<<EOT
     SELECT article_id, title FROM articles_info WHERE status=2 AND title REGEXP '^([0-9]{1,4}[/-]{0,1}[0-9]{0,4} +){0,1}($alpha[$i])+' ORDER BY title ASC
EOT;

  $res=mysql_query($query);
  $num_rows=mysql_num_rows($res);
  if ($num_rows>0) {
    $num_mssg="<P>These titles were brought to you by the letter <B><FONT SIZE=7>".strtoupper($alpha[$i])."</A></B>: $num_rows</P>";
    while ($d=mysql_fetch_object($res)) {
      $html_body .= "\n<TR><TD><a href='./article.phtml?id=$d->article_id'>$d->title</a></TD></TR>";
    }
  } else {
    $num_mssg = "<P>No results returned for the letter <B>$alpha[$i]</B>.</P>";
  }
}

$old=$i;
$i=1;
foreach ($alpha as $letter) {
  if ($i!=$old) {
    $nav .= "<a href='$PHP_SELF?i=$i'>$letter</a> ";
  } else {
    $nav .= "$letter ";
  }
  $i++;
}

echo <<<EOT
<P><FONT SIZE="5">$nav</FONT></P>

EOT;

if ($num_mssg) echo $num_mssg;
if ($html_body) echo "<TABLE>$html_body</TABLE>";

?>