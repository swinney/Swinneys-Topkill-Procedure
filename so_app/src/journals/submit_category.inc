<?
/*
 * $Id$
 */

require_once("Articles.php");
$a = new Articles();
$article = $a->getArticle($id,$db);

$html .="<P><B>$article[title]</B></P>";
if ($article[blurb]) {
    $html .="<P><B>$article[blurb]</B></P>";
}
$html .=<<<EOT
<P><B>by $article[username]</B></P>
$article[text]
EOT;

$html .= <<<EOT
<FORM NAME=category METHOD=POST ACTION="process_category.php">
<INPUT TYPE=HIDDEN NAME=id VALUE=$id>
EOT;
$category=$article[category];
if (isset($category)) {
  $query=<<<EOT
  SELECT name, 
         level1, 
         level1 & $category as sexy 
    FROM categories 
   WHERE name<>'' 
ORDER BY name ASC
EOT;

} else {
  $query=<<<EOT
  SELECT * 
    FROM categories 
ORDER BY name ASC
EOT;
}
  
$res = mysql_query($query);

# for the next loop, index
$i=0;

while ($d=mysql_fetch_object($res)) {

    $html .= "<input type='checkbox' name='cat[$i]' value='$d->level1'";
    if ($d->sexy!=0) {
      $html .= " CHECKED";
    }
    $html .= "> $d->name <br>\n";
    $i++;
} # child loop
$html .=<<<EOT
<INPUT TYPE=SUBMIT NAME="submit" VALUE="submit">
</FORM>
EOT;

echo $html;

?>







