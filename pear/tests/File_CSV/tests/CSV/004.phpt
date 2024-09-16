--TEST--
File_CSV Test Case 004: Unix EOL
--FILE--
<?php
// $Id: 004.phpt,v 1.3 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 * - File_CSV::discoverFormat()
 * - File_CSV::read()
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/004.csv';
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
?>
--EXPECT--
Format:
Array
(
    [fields] => 4
    [sep] => ,
    [quote] => "
)

Data:
Array
(
    [0] => Array
        (
            [0] => Field 1-1
            [1] => Field 1-2
            [2] => Field 1-3
            [3] => Field 1-4
        )

    [1] => Array
        (
            [0] => Field 2-1
            [1] => Field 2-2
            [2] => Field 2-3
            [3] => I'm multiline
Field
        )

    [2] => Array
        (
            [0] => Field 3-1
            [1] => Field 3-2
            [2] => Field 3-3
            [3] => 
        )

)
