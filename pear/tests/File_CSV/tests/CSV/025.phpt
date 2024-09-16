--TEST--
File_CSV Test Case 025: One row, four fields that are multiline with out a EOL and span couple of lines
--FILE--
<?php
// $Id: 025.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 * - Varian of test 011 but a lot longer
 * data gotten from http://www.creativyst.com/Doc/Articles/CSV/CSV01.htm
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/025.csv';
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
    [fields] => 4
    [sep] => ,
    [quote] => "
)

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
