<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$

$query = <<<EOT
  SELECT article_id,articles_info.username,title,web
    FROM articles_info,articles_user
   WHERE articles_info.article_id=articles_user.most_recent
EOT;
if (count($bozos)) {
  $query .= " AND articles_info.username NOT IN $bozo_set ";
}
$query .= <<<EOT
 ORDER BY article_id DESC
   LIMIT 15
EOT;

$res = mysql_query($query);

while ($d = mysql_fetch_object($res)) {
  // display title

  $username= stripslashes($d->username);
  if ($d->web != "") {
    $username=<<<EOT
 <a href="$d->web" target="_new">$username</a>
EOT;
  }

  echo <<<EOT
<p>
$username writes
<a href="journals/article.phtml?id=$d->article_id.txt">
<strong>$d->title</strong></a>
</p>

EOT;
}

?>
