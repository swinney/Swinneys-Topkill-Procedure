--TEST--
File_Util::isAbsolute() Windows support
--SKIPIF--
<?php
require_once 'File/Util.php';
if (!FILE_WIN32) {
  die('SKIP This test is only for Windows');
}
?>
--FILE--
<?php
// $Id: $
require_once 'File/Util.php';

var_dump(File_Util::isAbsolute('abra/../cadabra'));
var_dump(File_Util::isAbsolute('data/dir'));
var_dump(File_Util::isAbsolute('C:\\\\data'));
var_dump(File_Util::isAbsolute('d:/data'));
var_dump(File_Util::isAbsolute('\\'));
var_dump(File_Util::isAbsolute('/Progamme/xampp/htdocs'));
?>
--EXPECT--
bool(false)
bool(false)
bool(true)
bool(true)
bool(false)
bool(true)