--TEST--
File::writeChar()
--FILE--
<?php
require_once dirname(__FILE__) . DIRECTORY_SEPARATOR . 'setup.inc.php';

echo File::writeChar('test.txt', 'a') . "\n";
echo File::writeChar('test.txt', 'b') . "\n";
echo File::writeChar('test.txt', 'c') . "\n";
echo File::writeChar('test.txt', 'd') . "\n";
echo File::writeChar('test.txt', 'e') . "\n";
echo File::writeChar('test.txt', 'f') . "\n";
echo File::writeChar('test.txt', 'g') . "\n";
echo File::writeChar('test.txt', 'h') . "\n";
echo File::writeChar('test.txt', 'i') . "\n";
echo File::writeChar('test.txt', 'j') . "\n";
?>
--CLEAN--
<?php
require_once dirname(__FILE__) . '/teardown.inc.php';
?>
--EXPECT--
1
1
1
1
1
1
1
1
1
1