--TEST--
File_CSV Test Case bug14118: Error with quoted fields and separators
--FILE--
<?php
// $Id: bug14118-1.phpt,v 1.2 2008/10/26 21:39:02 dufuz Exp $
require_once 'File/CSV.php';
$path = dirname(__FILE__) . '/bug14118-1.csv';

$config = array(
    'sep'    => ',',
    'quote'  => '"',
    'fields' => 5
);
while ($row = File_CSV::read($path, $config)) {
    print_r($row);
}
?>
--EXPECT--
Array
(
    [0] => ENFB
    [1] => closed
    [2] => Oslo, Fornebu
    [3] => Airport
    [4] => 
)
Array
(
    [0] => ENFG
    [1] => medium_airport
    [2] => Leirin, Leirin
    [3] => Airport
    [4] => 
)
