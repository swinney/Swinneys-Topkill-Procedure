<?
/*
 * $Id$
 */

class Articles {

    //////////////////////////////////////////
    // get_article() -- retrieve the article info
    // this has to coincide with the use of the list() function
    // if the values as they are returned and their order in list()
    // do not align, there will be smoke.
    // austin, Tue Feb  5, 2002  1:35 PM

    function get_article($id,$db) {

        $query = <<<EOT
   SELECT articles_info.user_id,
          articles_info.username,
          articles_info.web,
          articles_info.date,
          articles_info.status,
          articles_info.title,
          articles_info.blurb,
          articles_info.category,
          articles_info.image,
          articles_text.text 
     FROM articles_info,articles_text
    WHERE articles_info.article_id=$id
      AND articles_info.article_id=articles_text.article_id
EOT;

	$row=$db->getRow($query); 
        $user_id    = $row[0];
        $username   = $row[1]; $username  =stripslashes($username);
        $web        = $row[2]; $web       =stripslashes($web);
        $date       = $row[3]; 
        $status     = $row[4];
        $title      = $row[5]; $title     =stripslashes($title);
        $blurb      = $row[6]; $blurb     =stripslashes($blurb);
        $category   = $row[7]; 
        $image      = $row[8];
        $text       = $row[9]; $text      =stripslashes($text);
        unset($row);
        $row        = array(
			    "user_id"=>$user_id,
			    "username"=>$username,
			    "web"=>$web,
			    "date"=>$date,
			    "status"=>$status,
			    "title"=>$title,
			    "blurb"=>$blurb,
			    "category"=>$category,
			    "image"=>$image,
			    "text"=>$text,
			    );
	return $row;
        unset($row);
    }  // end function get_article



    function get_articles($num) {
      global $id;
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
	       LIMIT $num
EOT;

	$res = mysql_query($query);

	while ($d = mysql_fetch_object($res)) {
	    $id=$d->article_id;
	    // display title
	    $names=get_cat_names($d->category);
	    $names=get_cat_none($names);
	    $username=stripslashes($d->username);
	    $url_username=urlencode(stripslashes($d->username));
	    $title=stripslashes($d->title);
	    $html .= <<<EOT
<P>
<a href="journals/userpages.phtml?username=$url_username">$username</a> writes
<a href="journals/article.phtml?id=$id">
<b>$title</b></a>
<br>
<font size=1>$names</FONT>
<BR>
</P>
EOT;
	}
	return $html;
    }




    function get_articles_rand($num) {
        global $id;
        // generate a set of 10 random ids just to hedge our bets, since we
        // could may be filtering a lot of bozos and some articles may no
        // longer be public
        $query = <<<EOT
	    SELECT article_id,username,title,date,web,category
	    FROM articles_info
	    WHERE status=2
EOT;
	if (count($bozos)) {
	    $query .= " AND user_id NOT IN $bozo_set ";
	}
	$query .= <<<EOT
	    ORDER BY RAND()
               LIMIT $num
EOT;

	$res = mysql_query($query);

	// multiple rows, limit 10 latest
	while ($d = mysql_fetch_object($res)) {
	    $id=$d->article_id;
	    $names=get_cat_names($d->category);
	    $names=get_cat_none($names);
	    $username = stripslashes($d->username);
	    $url_username=urlencode(stripslashes($d->username));
	    $title=stripslashes($d->title);
	    $html .= <<<EOT
<p>
<a href="journals/userpages.phtml?username=$url_username">$username</a> wrote
<a href="journals/article.phtml?id=$d->article_id">
<strong>$title</strong></a>
<BR>
<font size=1>$names</FONT>
<BR>
</p>
EOT;
	}
	return $html;
    }
} // end class
?>
