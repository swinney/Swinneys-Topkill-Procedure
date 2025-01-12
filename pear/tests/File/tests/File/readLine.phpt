--TEST--
File::readLine()
--FILE--
<?php
require_once dirname(__FILE__) . DIRECTORY_SEPARATOR . 'setup.inc.php';

var_dump(PEAR::isError(File::rewind('test.txt', FILE_MODE_READ)));
var_dump(($line === File::readLine('test.txt')));
var_dump(($line === File::readLine('test.txt')));
var_dump(($line === File::readLine('test.txt')));
var_dump(($line === File::readLine('test.txt')));
var_dump(($line === File::readLine('test.txt')));
var_dump(($line === File::readLine('test.txt')));
var_dump(($line === File::readLine('test.txt')));
var_dump(($line === File::readLine('test.txt')));
var_dump(($line === File::readLine('test.txt')));
var_dump(($line === File::readLine('test.txt')));
?>
--CLEAN--
<?php
require_once dirname(__FILE__) . '/teardown.inc.php';
?>
--EXPECT--
bool(false)
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