--TEST--
File_CSV Test Case 013: Reading ="" excel only fields
--FILE--
<?php
// $Id: 013.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 *   - Reading a ="" excel only field as normal "" field
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/013.csv';
$conf = File_CSV::discoverFormat($file);
$conf['quote'] = '"';
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
            [0] => 004343
            [1] =>    Helgi
            [2] =>  Project
multiline
stuff
        )

)
