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

    function getArticle($id,$db) {

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
			    "article_id"=>$id,
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



    function getTitles($order,$limit) {
      global $id;
       $query = <<<EOT
	 SELECT articles_info.article_id,
	 articles_info.username,
         articles_info.user_id,
	 articles_info.title,
	 articles_info.web,
	 articles_info.category
	 FROM articles_info,articles_front
   WHERE articles_info.article_id=articles_front.article_id
EOT;

	if (count($bozos)) {
	    $query .= " AND articles_info.user_id NOT IN $bozo_set ";
	}

	if ($order=="rand") {
	  $query .= " ORDER BY RAND()";
	} elseif($order=="id") {
	// lets try ordering by time
	  $query .= " ORDER BY article_id DESC";
	}
	$query .= " LIMIT $limit";

	$res = mysql_query($query);

	while ($d = mysql_fetch_object($res)) {
	    $aid=$d->article_id;
            $uid=$d->user_id;
	    // display title
	    if ($category=$d->category) {
	    $names=get_cat_names($category);
	    } else {
	    $names=get_cat_none($aid);
	    }
            unset($category);
	    $username=stripslashes($d->username);
	    $url_username=urlencode(stripslashes($d->username));
	    $title=stripslashes($d->title);
	    $html .= <<<EOT
<P>
<a href="journals/info_user.phtml?uid=$uid">$username</a> writes
<a href="journals/article.phtml?id=$aid">
<b>$title</b></a>
<br>
<font size=1>$names</FONT>
</P>
EOT;
	}
	return $html;
    }


    function getUserTitles($uid,$order,$limit) {
      global $id;
       $query = <<<EOT
	 SELECT articles_info.article_id,
	 articles_info.title,
	 articles_info.web,
	 articles_info.category
	 FROM articles_info
   WHERE articles_info.user_id=$uid
	 AND status IN (2,3)
EOT;
	if ($order=="rand") {
	  $query .= " ORDER BY RAND()";
	} elseif($order=="id") {
	// lets try ordering by time
	  $query .= " ORDER BY article_id DESC";
	}
	$query .= " LIMIT $limit";
	$res = mysql_query($query);

	while ($d = mysql_fetch_object($res)) {
	    $aid=$d->article_id;
            $uid=$d->user_id;
	    // display title
	    if ($category=$d->category) {
	    $names=get_cat_names($category);
	    } else {
	    $names=get_cat_none($aid);
	    }
            unset($category);
	    $username=stripslashes($d->username);
	    $url_username=urlencode(stripslashes($d->username));
	    $title=stripslashes($d->title);
	    $html .= <<<EOT
<P>
<a href="journals/article.phtml?id=$aid">
<b>$title</b></a>
<br>
<font size=1>$names</FONT>
</P>
EOT;
	}
        $html = "<P><B>5 most recent articles</B><BR><B><a href='userpages.phtml?uid=$uid'>&laquo; more from this writer</a></B></P>". $html;

	return $html;
    }

    function otherArticleId($a_article_id,$a_user_id,$flag,$db) {
      $query = <<<EOT
  SELECT article_id
    FROM articles_info
   WHERE article_id $flag $a_article_id
    AND user_id=$a_user_id
     AND status=2
ORDER BY article_id 
EOT;
      if ($flag=="<") {
	$query .= " DESC ";
      } elseif ($flag==">") {
	$query .= " ASC ";
      }
      $query .= " LIMIT 1";

      $id = $db->getOne($query);
      if (DB::isError($id)) {
	die($id->getMessage());
      }
      return $id;
    }


    /**
     *  function to increment the hit count on an article_id
     *  take article_id
     *  hit database to increment existing number.
     */
    function AddHit($db,$aid) {
      $query = "update articles_info set num_hits=num_hits+1 
                where article_id=$aid";
      $res=$db->query($query);
      if (DB::isError($res)) {
	die($res->getMessage());
      }
    }
}
?>
