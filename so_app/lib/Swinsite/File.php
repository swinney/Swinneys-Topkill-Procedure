<?php
//
require_once( CONF ."/". DB_NAME ."_conf.php");
class File {

  function getName($db,$aid,$file_id) {

    $query = 'SELECT filename, description 
              FROM articles_files 
              WHERE file_id='.$file_id.' 
              AND article_id='.$aid;
    $res = $db->query($query);
    if (DB::isError($db)) {
      die ($db->getMessage());
    }
    $row = $res->fetchRow();
    return $row;
  }

  function putName($db,$aid,$file_id,$filename,$description) {
    $filename=addslashes($filename);
    $description=addslashes($description);

    $query = 'UPDATE articles_files 
              SET filename="'.$filename.'",
              description="'.$description.'" 
              WHERE file_id='.$file_id.' 
              AND article_id='.$aid;
    if (ERROR_REP) {
      echo $query;
    }
    $db->query($query); 
    if (DB::isError($db)) {
      die ($db->getMessage());
    } else {
      return "TRUE";
    }
    
  }
  /**
   * Add a file's info to a row in the ARTICLES_FILES_TBL and increment
   * the IMAGE column of the parent row in ARTICLES_INFO_TBL.
   *
   * @param $db is the object database connection.  
   * See DB::connect method for more info.
   *
   * @param $aid is the AID (articled identification number) that does
   * associate this file with it's parent document.
   *
   * @param $file_id the identification number specific to the 
   * file whose row we are altering in ARTICLES_FILE_TBL
   *
   * @param $file_size is the size of the file in bytes.
   *
   * @param $ext the extension of the file; used to determine the file's
   * type.
   *
   * @return TRUE if the add is successful.
   *
   * @see DB::isError
   * @see DB::query
   * @see DB::getMessage
   */
 
  function addInfo($db,$aid,$file_id,$file_size,$filename,$ext) {
    $ext=end(explode(".",$filename));
    $filename=addslashes($filename);
    $description=addslashes($description);
    $query = 'INSERT INTO articles_files (article_id,file_id,filesize,ext,filename) VALUES ('.$aid.','.$file_id.','.$file_size.',"'.$ext.'","'.$filename.'")';
    $res = $db->query($query); 
    if (ERROR_REP) {
        $error_msg .="<P>The processing query was: $query</P>";
    }
    if (DB::isError($res)) {
      die($res->getMessage());
    }
    $query='UPDATE articles_info SET image='.$file_id.' WHERE article_id='.$aid;
    $res = $db->query($query); 
    if (ERROR_REP) {
        $error_msg .="<P>The image index query was: $query</P>";
    }
    if (DB::isError($res)) {
      die($res->getMessage());
    } else {
      return "TRUE";
    }
  }

    
/////////////////////////////////////////
// getNames() - retireve the image names
/////////////////////////////////////////

  function getNames($db,$aid) {
  //
  // show images if they exist
  //
    $img_name=array();
    $query = 'SELECT file_id,ext FROM articles_files WHERE article_id='.$aid;
    $res = $db->query($query);
    if(DB::isError($res)) {
      die($res->getMessage() . "<BR><BR>". $query);
    }
    while($row=$res->fetchRow()) {
      $img_name[]=$aid.'_'.$row[0].'.'.$row[1];
    }
    return $img_name;
  }

///////////////////////////////////////
// regexNames()
///////////////////////////////////////
  function regexNames($img,$text) {
   /** TODO: this should have been called file. 
    */
    preg_match_all("/(%{2})(file|img|pdf|doc|mp3)(\d{1,2})(%{2})/",$text,$out,PREG_PATTERN_ORDER);
    for ($i=0;isset($out[0][$i]);$i++) {
        $usekey=$out[3][$i]-1;
        $replace= SITE_IMGURL . "/" . $img[$usekey];
        $text=ereg_replace($out[0][$i],$replace,$text);
    }
    return $text;
  }

}
