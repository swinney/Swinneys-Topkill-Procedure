<!--
$Id$
-->
<?


include "next_article.inc";

  $article_id=$id;
  $res = mysql_query("SELECT * FROM articles_info WHERE article_id='$article_id'");
  $d = mysql_fetch_object( $res);
  
 
   echo "<H2>".stripslashes($d->title)."</h2>  ";
   echo "<h4>".stripslashes($d->blurb)."</h4>\n";

// check for URL or MAILTO

   $name = $d->username;
   $web = $d->web;
      if ($web == "") {
         echo "<h4>by $name</h4>\n";
      } else {
         echo "<h4>by <a href='".$d->web."'> ".stripslashes($d->username)."</a><br> $d->date</h4>\n";
      }

 
// open that file up

$text = explode(".",$article_id);

$res = mysql_query ("SELECT text FROM articles_text WHERE article_id=$text[0]");

$d = mysql_fetch_row($res);

echo "$d[0]<BR>";

?>










