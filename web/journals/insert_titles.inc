<?
// -*- Mode: PHP; indent-tabs-mode: nil; -*-
// $Id$

// declare this array outside the loop
$writes = array( 1 => 
		 'mounts the campaign for good in',
		 'scores a point on mcsweeny with',
		 'utters a plaintif wail, listen',
		 'tempts readers,',
		 'subverts in',
		 'redefines the dominant paradigm with',
		 'challenges the status quo, read it:',
		 'assesses reality in',
		 'whispers in your ear',
		 'writes on the wall:',
		 'speaks out:',
		 'makes the grade with',
		 'casts a message in a bottle called',
		 'hides a note in your purse that reads',
		 'simpers',
		 'writes',
		 'pens',
		 'scribes',
		 'whips out',
		 'jots',
		 'notes',
		 'scrawls',
		 'scribbles',
		 'drafts',
		 'whips off',
		 'makes another swinney with',
		 'clarifies',
		 'shares',
		 'steals the narrative with',
		 'makes a statement with',
		 'howles',
		 'enunciates with',
		 'with forked tongue speaks',
		 'defines the <I>rules of engagement</I> in'
		 );

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
<a href="$d->web" target="_new"> $username</a>
EOT;
  }

  $num = dice(1, count($writes));

  echo <<<EOT
<p>
$username $writes[$num]
<a href="journals/article.phtml?id=$d->article_id.txt">
<strong>$d->title</strong></a>
</p>

EOT;
}

?>
