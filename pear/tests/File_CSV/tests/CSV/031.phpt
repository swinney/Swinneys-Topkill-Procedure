--TEST--
File_CSV Test Case 031: One row, four fields that are multiline with out a EOL and span couple of lines
--FILE--
<?php
// $Id: 031.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 * - Varian of test 026 but doesn't have to detect the config
 * data gotten from http://www.creativyst.com/Doc/Articles/CSV/CSV01.htm
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/031.csv';
$conf = array(
    'fields' => 3,
    'sep'    => ',',
    'quote'  => '"'
);

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
            [0] => Conference room 1
            [1] => John,
Please bring the M. Mathers file for review
-J.L.

            [2] => 10/18/2002
        )

)
