<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$

// generate a set of 10 random ids just to hedge our bets, since we
// could may be filtering a lot of bozos and some articles may no
// longer be public
$rand = array();
for ($i=0; $i<10; $i++) {
  array_push($rand, dice(1, 1000));
}
$rand_set = '(' . implode(', ', $rand) . ')';

$query = <<<EOT
  SELECT article_id,username,title,date,web
    FROM articles_info
   WHERE status=2
     AND article_id IN $rand_set
EOT;
if (count($bozos)) {
  $query .= " AND username NOT IN $bozo_set ";
}
$query .= <<<EOT
ORDER BY time
   LIMIT 5
EOT;

$res = mysql_query($query);

// multiple rows, limit 10 latest
while ($d = mysql_fetch_object($res)) {
    $username = $d->username;

  echo <<<EOT
<p>
<a href="journals/userpages.phtml?username=$username">$username</a> wrote
<a href="journals/article.phtml?id=$d->article_id.txt">
<strong>$d->title</strong></a>
</p>

EOT;
}

?>



