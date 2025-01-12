--TEST--
File_Uti::listDir()
--FILE--
<?php
// $Id: $
require_once 'File/Util.php';

$dir = dirname(__FILE__) . DIRECTORY_SEPARATOR . 'listDir';
$dirs = File_Util::listDir($dir, FILE_LIST_ALL &~ FILE_LIST_DOTS);
foreach ($dirs as $k => $v) {
  unset($dirs[$k]->date); // date is modified time, can't be tested for reliably
}
print_r($dirs);
?>
--EXPECT--
Array
(
    [0] => stdClass Object
        (
            [name] => bug14030-to-delete.csv
            [size] => 161
        )

    [1] => stdClass Object
        (
            [name] => parser.php
            [size] => 577
        )

    [2] => stdClass Object
        (
            [name] => test.csv
            [size] => 537
        )

)
