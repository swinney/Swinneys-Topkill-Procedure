<?php
require_once("global.inc");

class Multi {

    function is_multi($id) {
        $query =<<<EOT
SELECT count(multi_articles.article_id) as num 
  FROM multi_articles 
 WHERE article_id=$id
EOT;
        $res=mysql_query($query);
        $num=mysql_result($res,0);
        return $num;
    }

    function get_multi($id) {
        $query =<<<EOT
      SELECT multi_info.multi_id,
             multi_info.user_id as editor_id,
             multi_info.title as multi_title,
             multi_articles.article_id, 
             articles_info.title,
             articles_info.blurb,
             articles_info.username as multi_username
        FROM multi_info,
             multi_articles,
             articles_info 
       WHERE multi_info.user_id=17 
         AND multi_info.multi_id=multi_articles.multi_id 
         AND articles_info.article_id=multi_articles.article_id
EOT;
        $res = mysql_query($query);
        while ($d=mysql_fetch_object($res)) {
	    if (!$html) {
                $multi_username=get_username($d->editor_id);
	        /* 
	         * FIRST start by getting the title of the multi
	         */
	        $html= <<<EOT
<P><B><a href='./multi_info.phtml?mid=$d->multi_id'>$d->multi_title</a></B>\n
<BR>edited by <a href="./userpages.phtml?username=$multi_username">$multi_username</A></P>\n
EOT;
            }
            /*
             * NOW start getting the articles in the multi
	     */
	    if ($d->article_id!=$id) {
	        $html .= "<P><A HREF=\"./article.phtml?id=$d->article_id\"><B>$d->title</B></A> ";
	        if ($d->blurb) {
	            $html .="<BR>$d->blurb ";
	        }
	        $html .="by $d->multi_username</P>\n";
	    } else {
	        $html .="<P>Currently Viewing!</P>";
	    }
	}
        echo <<<EOT
<!-- Right Margin Matter Box -->
</TD>
<td width="33">
<img src="http://swinney.org/dev/journals/img/no.gif" alt="" width="33" height="1" border="0"></td>
<TD WIDTH="150" ALIGN=RIGHT VALIGN=TOP>
<IMG SRC="img/rollcall.gif">
$html
</TD>
EOT;
    }
}

?>





