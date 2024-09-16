--TEST--
File_CSV Test Case 008: Various different lines.
--FILE--
<?php
// $Id: 008.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 * - parsing, separators within quotes
 * data gotten from http://www.creativyst.com/Doc/Articles/CSV/CSV01.htm
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/008.csv';
$conf = File_CSV::discoverFormat($file);


$data = array();
while ($res = File_CSV::read($file, $conf)) {
    $data[] = $res;
}

print "Data:\n";
print_r($data);
print "\n";
?>
--EXPECT--
Data:
Array
(
    [0] => Array
        (
            [0] => Joan the bone, Anne
            [1] => Jet
            [2] => 9th, at Terrace plc
            [3] => Desert City
            [4] => CO
            [5] => 00123
        )

)
