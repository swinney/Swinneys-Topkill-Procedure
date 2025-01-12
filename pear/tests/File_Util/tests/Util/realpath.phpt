--TEST--
File_Util::realPath()
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

var_dump((('/a/weird/path/is' === File_Util::realpath('/a\\weird//path\is/that/./../', '/')) ? true : false));
var_dump((('/a/weird/path/is/that' == File_Util::realpath('/a\\weird//path\is/that/./../that/.', '/')) ? true : false));
?>
--EXPECT--
bool(true)
bool(true)