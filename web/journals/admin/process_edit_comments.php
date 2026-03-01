<?
// $Id$
include("../global.php");

$res = $db->query("UPDATE comments
                    SET comment='$comment',
                        timestamp=$timestamp,
                        status=$status
                    WHERE comment_id=$comment_id");

  if (DB::isError($res)) {
     echo "update failed for:";
  }

if ($previous==0) {
   $location="admin_comments.php";
}

if ($previous==1) {
   $location="admin_comments_article.php?article_id=$article_id";
}


header("Location: $location");

?>




