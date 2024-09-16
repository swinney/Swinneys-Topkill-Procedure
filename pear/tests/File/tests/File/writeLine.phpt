--TEST--
File::writeLine()
--FILE--
<?php
require_once dirname(__FILE__) . DIRECTORY_SEPARATOR . 'setup.inc.php';

$length = strlen($line) + 1;
var_dump(($length === File::writeLine('test.txt', $line)));
var_dump(($length === File::writeLine('test.txt', $line)));
var_dump(($length === File::writeLine('test.txt', $line)));
var_dump(($length === File::writeLine('test.txt', $line)));
var_dump(($length === File::writeLine('test.txt', $line)));
var_dump(($length === File::writeLine('test.txt', $line)));
var_dump(($length === File::writeLine('test.txt', $line)));
var_dump(($length === File::writeLine('test.txt', $line)));
var_dump(($length === File::writeLine('test.txt', $line)));
var_dump(($length === File::writeLine('test.txt', $line)));
?>
--CLEAN--
<?php
require_once dirname(__FILE__) . '/teardown.inc.php';
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)