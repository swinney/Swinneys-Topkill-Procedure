<?php
require_once("global.php");

class Multi {

    function get_multi_id($id) {
        $query = "SELECT multi_id FROM multi_articles WHERE article_id=$id";
        $res = $db->query($query);
        $mid = $res->fetchOne();
        return $mid;
    }

    function get_nav($multi_id) {
return <<<EOT
<P>
<A HREF="./index_multi.php">Index</a> |
<A HREF="./info_multi.php?multi_id=$multi_id">View Info</A> |
<A HREF="./submit_title.php?multi_id=$multi_id">Edit Title</A> | 
<A HREF="./submit_abstract.php?multi_id=$multi_id">Edit Abstract</A> |
<A HREF="./submit_multi.php?multi_id=$multi_id">Add Articles</a>
</P>
EOT;
    }

    function get_abstract($mid) {
        $query = "SELECT abstract FROM multi_info WHERE multi_id=$mid";
        $res = mysql_query($query);
        $abstract = stripslashes(mysql_result($res,0));
        return $abstract;
    } 

    function get_multi_fm_id ($mid) {
        $query .= <<<EOT
  SELECT multi_info.user_id,multi_info.title,multi_info.abstract FROM multi_info WHERE multi_info.multi_id=$mid
EOT;
        $res=mysql_query($query);
        $row=mysql_fetch_array($res);
        return $row;
    }

    function is_multi($id) {
        global $db;
        $query =<<<EOT
      SELECT count(multi_articles.article_id) as num, 
                 multi_articles.multi_id as multi_id 
            FROM multi_articles 
           WHERE article_id=$id
        GROUP BY multi_id
EOT;
        $d = $db->query($query);
        if ($d->numRows() == 0) {
            $num[0] = 0;
            $num[1] = 0;
            return $num;
        } else {
            $row = $d->fetchRow(DB_FETCHMODE_OBJECT);
            $num[0] = $row->num;
            $num[1] = $row->multi_id;
            return $num;
        }
    }
    function get_multi($id,$multi_id,$location) {
        $query =<<<EOT
      SELECT multi_info.user_id as editor_id,
             multi_info.title as multi_title,
             multi_articles.article_id, 
             articles_info.title,
             articles_info.blurb,
	  articles_info.username as multi_username,
             articles_info.user_id as multi_user_id
        FROM multi_info,
             multi_articles,
             articles_info 
       WHERE multi_info.multi_id=$multi_id 
         AND multi_articles.multi_id=$multi_id
         AND articles_info.article_id=multi_articles.article_id
    ORDER BY multi_articles.article_id
EOT;
        $res = $db->query($query);
        while ($d = $res->fetchRow(DB_FETCHMODE_OBJECT)) {
	        $multi_title = stripslashes($d->multi_title);
	        $multi_username = stripslashes($d->multi_username);
            $title = stripslashes($d->title);
	        $blurb = stripslashes($d->blurb);
            $multi_user_id = $d->multi_user_id;
	        if (!$html && $location=="right") {
                $editor_username=get_username($d->editor_id);
	        /* 
	         * FIRST start by getting the title of the multi
	         */
	        $html= <<<EOT
<P><B><a href='./multi_info.php?mid=$multi_id'>$multi_title</a></B>\n
<BR>edited by <a href="./info_user.php?uid=$d->editor_id">$editor_username</A></P>\n
EOT;
            }
            /*
             * NOW start getting the articles in the multi
	     */
	    if ($d->article_id) {
	      $html .= "<P>";
	        if ($d->article_id==$id) {
		    $html .= "<SUP>(Currently Viewing)</SUP><BR>";
	        }

	        $html .= "<A HREF=\"./article.php?id=$d->article_id\"><B>$title</B></A> ";
	        if ($d->blurb) {
	            $html .="<BR>$blurb ";
	        }
	        $html .="<BR>by <a href='info_user.php?uid=$multi_user_id'>$multi_username</A>\n";
                $html .="</P>";

	    }
	}

	if ($location=="right") {
        return <<<EOT
<!-- Right Margin Matter Box -->
</TD>
<td width="33">
<img src="http://swinney.org/dev/journals/img/no.gif" alt="" width="33" height="1" border="0"></td>
<TD WIDTH="150" ALIGN=RIGHT VALIGN=TOP>
<IMG SRC="img/serial.gif">
$html
</TD>
EOT;
	} elseif ($location=="inline") {
	  return $html;

	}
    }
}
?>
