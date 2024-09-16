--TEST--
File_Util::tmpDir()
--FILE--
<?php
// $Id: $
require_once 'File/Util.php';

$dir = File_Util::tmpDir();
var_dump(is_dir($dir));
?>
--EXPECT--
bool(true)
