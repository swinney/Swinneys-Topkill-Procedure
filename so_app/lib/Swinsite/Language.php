<?php   // -*- Mode: PHP; indent-tabs-mode: nil; -*-

require_once("Bozos.php");
require_once("DBPeer/UserPeer.php");
require_once("Persistent/Object.php");

class Language {

  function parenLang($sess_lang) {
    $lang_str = implode("','",$sess_lang);
    $lang_str = "('$lang_str')";
    return $lang_str;
  }
}
