--TEST--
File_CSV Test Case 010: Empty first field and no quoting but some fields have extra spacing
--FILE--
<?php
// $Id: 010.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 * - parsing, how we handle quotes and separators inside quotes
 *   and empty fields
 * data gotten from http://www.creativyst.com/Doc/Articles/CSV/CSV01.htm
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/010.csv';
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
            [0] => 
            [1] => Blankman
            [2] => 
            [3] => SomeTown
            [4] => SD
            [5] => 00298
        )

)
