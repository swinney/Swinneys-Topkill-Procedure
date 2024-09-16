--TEST--
File_CSV Test Case 019: Various different lines.
--FILE--
<?php
// $Id: 019.phpt,v 1.3 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 * - parsing, separators and quotes within quotes
 * - Identical to 016 beside it removes the sep after the double
 *   quote
 * data gotten from http://www.creativyst.com/Doc/Articles/CSV/CSV01.htm
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/019.csv';
$conf = File_CSV::discoverFormat($file);

print "Format:\n";
print_r($conf);
print "\n";

$data = array();
while ($res = File_CSV::read($file, $conf)) {
    $data[] = $res;
}

print "Data:\n";
print_r($data);
print "\n";
?>
--EXPECT--
Format:
Array
(
    [fields] => 6
    [sep] => ,
    [quote] => "
)

Data:
Array
(
    [0] => Array
        (
            [0] => Joan "the bone" Anne
            [1] => Jet
            [2] => 9th, at Terrace plc
            [3] => Desert City
            [4] => CO
            [5] => 00123
        )

)
