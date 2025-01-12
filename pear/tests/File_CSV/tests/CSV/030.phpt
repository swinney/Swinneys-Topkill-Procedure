--TEST--
File_CSV Test Case 030: One row, four fields that are multiline with out a EOL and span couple of lines
--FILE--
<?php
// $Id: 030.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 * - Varian of test 025 but doesn't have to detect the config
 * data gotten from http://www.creativyst.com/Doc/Articles/CSV/CSV01.htm
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/030.csv';
$conf = array(
    'fields' => 4,
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
            [0] => I'm multiline
Field
that spans
over couple
of
rather odd
sections
of the
world
            [1] => Helgi
            [2] => foobar
            [3] => And I'm another
multiline beast
that spans
couple of
lines
in
this
document
        )

)
