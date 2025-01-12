--TEST--
File_CSV Test Case 023: Only one field that's multiline with out a EOL and a potential quote inside quotes
--FILE--
<?php
// $Id: 023.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 * - parsing, how we handle quotes and separators inside quotes
 *   and empty fields
 * - Varian of test 011
 * data gotten from http://www.creativyst.com/Doc/Articles/CSV/CSV01.htm
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/023.csv';
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
    [fields] => 1
    [sep] => ,
    [quote] => '
)

Data:
Array
(
    [0] => Array
        (
            [0] => I"m multiline
Field
        )

)
