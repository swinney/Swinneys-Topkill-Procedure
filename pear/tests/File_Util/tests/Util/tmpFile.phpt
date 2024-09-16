--TEST--
File_Util::tmpFile()
--FILE--
<?php
// $Id: $
require_once 'File/Util.php';
$tmp = File_Util::tmpFile();
var_dump(file_exists($tmp));
?>
--EXPECT--
bool(true)
