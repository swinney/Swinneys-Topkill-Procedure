<?php
###################################
# $Id$
# bring the articles
require_once ("HTML/IT.php");
require_once ("./global.php");
//
// take care of the id
$chunks = explode(".", $id);
$id = $chunks[0];

$page_title = "Articles by All";

$article_row=get_article($id,$db);

list( // of $article_row
     $user_id,
     $username,
     $web,
     $date,
     $status,
     $title,
     $blurb,
     $category,
     $image,
     $text
     ) = $article_row;
/*
 * strip the slashes
 */
// not on user_id
$username=stripslashes($username);
$web=stripslashes($web);
// not on date
// not on status
$title = stripslashes($title);
$blurb = stripslashes($blurb);
// not on category
// not on image
$text = stripslashes($text);

if ($image>0) {
require_once("Madmin/Image.php");
$Image = new Image();
$img_array = $Image->get_img($image,$id);
$text = $Image->show_img($img_array,$text);
}

$tpl = new IntegratedTemplate(INCDIR ."");
  $tpl->loadTemplatefile("article.html", true, true);

     if (SITE_NAME)
     $tpl->setVariable("site_name", SITE_NAME);
     if ($page_title)
     $tpl->setVariable("page_title", $page_title);
     if (CSS_URL)
     $tpl->setVariable("css_url", CSS_URL);
     if ($rollcall=get_rollcall())
     $tpl->setVariable("rollcall", $rollcall);
     //
     // now these come from the sql
     if ($user_id)
     $tpl->setVariable("user_id", $user_id);
     if ($username)
     $tpl->setVariable("username",$username);
     if ($web)
     $tpl->setVariable("web", $web);
     if ($date)
     $tpl->setVariable("date", $date);
     if ($status)
     $tpl->setVariable("status", $status);
     if ($title)
     $tpl->setVariable("title", $title);
     if ($blurb)
     $tpl->setVariable("blurb", $blurb);
     if ($category)
     $tpl->setVariable("category", $category);
     // TODO: image parsing
     // 
     if ($text)
     $tpl->setVariable("text", $text);
     if ($comments=get_comments($id,$db)) 
     $tpl->setVariable("comments", $comments);

$tpl->parseCurrentBlock();
$tpl->show();

?>
