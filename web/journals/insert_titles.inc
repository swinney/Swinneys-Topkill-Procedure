<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$

$query = <<<EOT
SELECT article_id,username,title,web,category
    FROM articles_info WHERE status=2
EOT;
if (count($bozos)) {
  $query .= " AND articles_info.user_id NOT IN $bozo_set ";
}
// lets try ordering by time
$query .= <<<EOT
 ORDER BY time DESC
   LIMIT 10
EOT;

$res = mysql_query($query);

while ($d = mysql_fetch_object($res)) {
  // display title
  $names=get_cat_names($d->category);
  $username=stripslashes($d->username);
  $url_username=urlencode(stripslashes($d->username));
  $title=stripslashes($d->title);
  echo <<<EOT
<P>
<a href="journals/userpages.phtml?username=$url_username">$username</a> writes
<a href="journals/article.phtml?id=$d->article_id.txt">
<b>$title</b></a>
<br>
<font size=1>$names</FONT>
<BR>
</P>
EOT;
}
?>
