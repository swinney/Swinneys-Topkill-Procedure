--TEST--
File_Util::skipRoot()
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
echo File_Util::skipRoot('/usr/share/pear');
?>
--EXPECT--
usr/share/pear