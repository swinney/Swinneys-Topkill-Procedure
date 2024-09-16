--TEST--
File_Util::skipRoot() Windows support
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

echo File_Util::skipRoot('C:\\WINDOWS') . "\n";
echo File_Util::skipRoot('C:\\\\WINDOWS') . "\n";
echo File_Util::skipRoot('C:/WINDOWS');
?>
--EXPECT--
WINDOWS
WINDOWS
WINDOWS