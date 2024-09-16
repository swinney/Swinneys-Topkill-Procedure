--TEST--
File::readChar()
--FILE--
<?php
require_once dirname(__FILE__) . DIRECTORY_SEPARATOR . 'setup.inc.php';

var_dump(PEAR::isError(File::rewind('test.txt', FILE_MODE_READ)));
echo File::readChar('test.txt') . "\n";
echo File::readChar('test.txt') . "\n";
echo File::readChar('test.txt') . "\n";
echo File::readChar('test.txt') . "\n";
echo File::readChar('test.txt') . "\n";
echo File::readChar('test.txt') . "\n";
echo File::readChar('test.txt') . "\n";
echo File::readChar('test.txt') . "\n";
echo File::readChar('test.txt') . "\n";
echo File::readChar('test.txt') . "\n";
echo File::readChar('test.txt') . "\n";
?>
--CLEAN--
<?php
require_once dirname(__FILE__) . '/teardown.inc.php';
?>
--EXPECT--
bool(false)
0
1
2
3
4
5
6
7
8
9
0