<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$

// generate a set of 10 random ids just to hedge our bets, since we
// could may be filtering a lot of bozos and some articles may no
// longer be public
$query = <<<EOT
SELECT article_id,username,title,date,web,category
    FROM articles_info
   WHERE status=2
EOT;
if (count($bozos)) {
  $query .= " AND username NOT IN $bozo_set ";
}
$query .= <<<EOT
 ORDER BY RAND()
   LIMIT 10
EOT;

$res = mysql_query($query);

// multiple rows, limit 10 latest
while ($d = mysql_fetch_object($res)) {
    $names=get_cat_names($d->category);
    $username = $d->username;

  echo <<<EOT
<p>
<a href="journals/userpages.phtml?username=$username">$username</a> wrote
<a href="journals/article.phtml?id=$d->article_id.txt">
<strong>$d->title</strong></a>
<BR>
<font size=1>$names</FONT>
<BR>
</p>

EOT;
}

?>



