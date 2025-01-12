--TEST--
File::read()
--FILE--
<?php
require_once dirname(__FILE__) . DIRECTORY_SEPARATOR . 'setup.inc.php';

var_dump(($line === File::read('test.txt', 10000)));
echo File::read('test.txt', 1);
echo File::read('test.txt', 10);
?>
--CLEAN--
<?php
require_once dirname(__FILE__) . '/teardown.inc.php';
?>
--EXPECT--
bool(true)

0123456789