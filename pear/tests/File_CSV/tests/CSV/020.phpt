--TEST--
File_CSV Test Case 020: First field quoted = last field being excluded
--FILE--
<?php
// $Id: 020.phpt,v 1.3 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 *   - odd quote behaviour in discoverFormat excludes the last field
 *     When the first field is quoted and the next field is not then
 *     the last field is popped off
 *   - Happens because when the first and last/second last fields
 *     are quoted but not the middle ones it thinks they are inside the
 *     quotes and thus one to few fields but the read process works things
 *     out perfectly, only discoverFormat messes up
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/020.csv';
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
    [fields] => 5
    [sep] => ,
    [quote] => "
)

Data:
Array
(
    [0] => Array
        (
            [0] => 004343
            [1] => Helgi
            [2] => Project
            [3] => 007
            [4] => 008
        )

)
