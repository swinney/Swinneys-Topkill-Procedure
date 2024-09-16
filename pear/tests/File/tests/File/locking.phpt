--TEST--
File Locking
--FILE--
<?php
require_once dirname(__FILE__) . DIRECTORY_SEPARATOR . 'setup.inc.php';

var_dump(PEAR::isError(File::write('test.txt', 'abc', FILE_MODE_APPEND, true)));
var_dump(PEAR::isError(File::write('test.txt', 'def', FILE_MODE_WRITE, true)));
var_dump(PEAR::isError(File::unlock('test.txt', FILE_MODE_APPEND)));
var_dump(PEAR::isError(File::unlock('test.txt', FILE_MODE_WRITE)));
?>
--CLEAN--
<?php
require_once dirname(__FILE__) . '/teardown.inc.php';
?>
--EXPECT--
bool(false)
bool(true)
bool(false)
bool(false)