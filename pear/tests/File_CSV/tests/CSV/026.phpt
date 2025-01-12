--TEST--
File_CSV Test Case 026: One row, four fields that are multiline with out a EOL and span couple of lines
--FILE--
<?php
// $Id: 026.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 * - Varian of test 011 but a lot longer
 * data gotten from http://www.creativyst.com/Doc/Articles/CSV/CSV01.htm
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/026.csv';
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
    [fields] => 3
    [sep] => ,
    [quote] => "
)

Data:
Array
(
    [0] => Array
        (
            [0] => Conference room 1
            [1] => John,
Please bring the M. Mathers file for review
-J.L.

            [2] => 10/18/2002
        )

)
