--TEST--
File_Util::relativePath()
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

echo File_Util::relativePath('/usr/share/pear/tests/File', '/usr/share/pear', '/') . "\n";
echo File_Util::relativePath('/etc', '/usr', '/') . "\n";
echo File_Util::relativePath('data', 'data/dir', '/') . "\n";
echo File_Util::relativePath('/var/data/dir', '/var');
?>
--EXPECT--
tests/File
../etc
../
data/dir