<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$

$query = <<<EOT
SELECT article_id,articles_info.username,title,web,category
    FROM articles_info,articles_user
   WHERE articles_info.article_id=articles_user.most_recent
EOT;
if (count($bozos)) {
  $query .= " AND articles_info.username NOT IN $bozo_set ";
}
$query .= <<<EOT
 ORDER BY article_id DESC
   LIMIT 10
EOT;

$res = mysql_query($query);

while ($d = mysql_fetch_object($res)) {
  // display title
  $names=get_cat_names($d->category);
  $username= stripslashes($d->username);

  echo <<<EOT
<P>
<a href="journals/userpages.phtml?username=$username">$username</a> writes
<a href="journals/article.phtml?id=$d->article_id.txt">
<b>$d->title</b></a>
<br>
<font size=1>$names</FONT>
<BR>
</P>
EOT;
}
?>
