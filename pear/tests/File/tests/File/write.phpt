--TEST--
File::write()
--FILE--
<?php
require_once dirname(__FILE__) . DIRECTORY_SEPARATOR . 'setup.inc.php';

$bytes = File::write('test.txt', '0123456789');
var_dump(PEAR::isError($bytes));
echo $bytes;
?>
--CLEAN--
<?php
require_once dirname(__FILE__) . '/teardown.inc.php';
?>
--EXPECT--
bool(false)
10