
<!--insert_article.inc-->
<?

include "connect.inc";

//  $url = "/article.phtml?id=$article_id";
  $article_id=$id;
  $res = mysql( "", "SELECT * FROM pending_articles WHERE article_id='$article_id'");
  $d = mysql_fetch_object( $res);
 
 
   echo "<h2>$d->title</h2>  ";
   echo "<h4>$d->blurb</h4>\n";

 

$fp = fopen("pending/$article_id", "r");
  if ( $fp == false ) {
    echo "Could not open file!";
    echo "<br>$article_id.txt";
    exit;
  }
  fpassthru($fp);



?>