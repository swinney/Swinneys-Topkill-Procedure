<?
##############################################
# $Id$
require_once("./global.php");

if (isset($submit_image)) {
  if ($aindex) {
    $aindex=$aindex+1;
  } else {
    $query = 'SELECT COUNT('. AID .') 
              FROM '. ARTICLES_FILES_TBL .' 
              WHERE '. AID .'='. $article_id;
    $aindex = $db->getOne($query);

    if (!$aindex) {
      $aindex=1;
    } else {
      $aindex++;
    }
  }
  $error_msg .= "<BR>aindex is $aindex<BR>";
    $ext=substr("$userfile_name",-3);
    if ($ext == "peg") {
        $ext = "jpg";
    }
    // dont name them zero, if there arnet any yet.
    $filename = $article_id . "_" . $aindex . "." . $ext;
}

// Copy the file to our uploads directory
$filesize = filesize($userfile);

$copy=copy($userfile, IMGBASE ."/". $filename);

if (ERROR_REP) {
$error_msg .= "<P>The copy() of $filename returned $copy.</P>";
}

if ($copy=="TRUE") {
  $query = 'UPDATE '. ARTICLES_INFO_TBL .' 
            SET '. IMAGE .'='. IMAGE .'+1
            WHERE '. AID .'='. $article_id;
  if (mysql_query($query)) {
  $error_msg .= "<P>Update went fine.</P>";
  } else {
  // XXX: partially committed transaction! how to handle?
    $error_msg .= "<P>Error updating database: " . mysql_error() ."</P>";
  }
  include_once("File.php");
  $f = new File();
  $f->addInfo($db,$article_id,$aindex,$filesize,$userfile_name,$ext);

} elseif ($copy=="TRUE" && $over) {
  $error_msg .= "Success.  File has been copied over.";
} elseif (!$copy=="TRUE") {
  $error_msg .= "Error saving image $userfile to ". IMGBASE .".";
          // roll back the index since the file wasn't moved
}

if ($submit_image=="submit") {
  header("Location: submit_image.php?article_id=$article_id&index=$aindex");
} else if ($exit=="exit") {
  header("Location: ../journals/article.php?id=$article_id");
}

?>



