--TEST--
File_Util::isAbsolute()
--SKIPIF--
<?php
require_once 'File/Util.php';
if (FILE_WIN32) {
  die('SKIP This test is not for Windows');
}
?>
--FILE--
<?php
// $Id: $
require_once 'File/Util.php';

var_dump(File_Util::isAbsolute('abra/../cadabra'));
var_dump(File_Util::isAbsolute('data/dir'));
var_dump(File_Util::isAbsolute('/'));
var_dump(File_Util::isAbsolute('\\'));
var_dump(File_Util::isAbsolute('~mike/bin'));
var_dump(File_Util::isAbsolute('/Progamme/xampp/htdocs'));
?>
--EXPECT--
bool(false)
bool(false)
bool(true)
bool(false)
bool(true)
bool(true)