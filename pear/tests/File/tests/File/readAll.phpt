--TEST--
File::readAll()
--FILE--
<?php
require_once dirname(__FILE__) . DIRECTORY_SEPARATOR . 'setup.inc.php';

var_dump(($str === File::readAll('test.txt')));
var_dump(($str === File::readAll('test.txt')));
var_dump(($str === File::readAll('test.txt')));
?>
--CLEAN--
<?php
require_once dirname(__FILE__) . '/teardown.inc.php';
?>
--EXPECT--
bool(true)
bool(true)
bool(true)