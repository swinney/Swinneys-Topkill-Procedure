<?php
require_once("./global.php");

// take care of the id from back when it was a text file ( 1.txt )
$id = $_GET['id'];
if (isset($id)) {
  if (is_numeric($id)) {
    $article_id = $id;
  } else {
    $chunks = explode(".", $id);
    $article_id = $chunks[0];
  }
} else {
  $article_id = 0;
}

include_once("Articles.php");
$a = new Articles($db);
$a->AddHit($db, $article_id);
$row = $a->getArticle($article_id, $db);

$a_article_id = $row['article_id'];
$a_user_id    = $row['user_id']; 
$a_username   = stripslashes($row['username']);
$a_date       = stripslashes($row['date']);
$a_status     = $row['status'];
$a_title      = stripslashes($row['title']);
$a_blurb      = stripslashes($row['blurb']);
$a_category   = $row['category'];
$a_image      = $row['image'];
$a_text       = stripslashes($row['text']);
$a_keywords   = @stripslashes($row['keywords']);

unset($row);
if ($a_image > 0) {
    $imgurl=IMGURL;
    $query = "SELECT file_id, ext, filename, description 
              FROM articles_files 
              WHERE article_id=$a_article_id 
              ORDER BY file_id";
    $res = $db->query($query);

    $i=0;
    while ($row = $res->fetchRow()) {

      $file_id   = $row[0];
      $ext       = $row[1];
      $given     = $row[2];
      $desc      = $row[3];
      $img_loc   = $id .'_'. $file_id .'.'. $ext;
      if ($img_names) {
        array_push($img_names, "$img_loc");
      } else {
        $img_names = array("$img_loc");
      }
    }  
    include_once("File.php");
    $f = new File();
    var_dump($img_names);
    
    $a_text = $f->regexNames($img_names,$a_text);
}

$p_article_id = $a->otherArticleId($a_article_id,$a_user_id,"<",$db);
$n_article_id = $a->otherArticleId($a_article_id,$a_user_id,">",$db);

// if they dont have an article id, then
// they should not be here, or their status is 4 (deleted)
if (@$status==4) {
  header("Location: ./index.php?no_aricle_id");
  exit();
}
if (isset($a_title))
$title = "$a_title by $a_username";
$into_template="insert_article.inc";
// do you have comments?
$into_template2="insert_comments.php";
# is rollcall.inc displayed?
# 0 for norollcall.inc; 1 for rollcall.inc.
$rollcall=1;

include_once("./templates/template.inc");

?>
