--TEST--
File_CSV Test Case 027: Records with spaces around them but no quotes
--FILE--
<?php
// $Id: 027.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * data gotten from http://www.creativyst.com/Doc/Articles/CSV/CSV01.htm
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/027.csv';
$conf = File_CSV::discoverFormat($file);

print "Format:\n";
echo 'fields: ' . $conf['fields'] . "\n";
echo "sep:\n";
File_CSV::_dbgBuff($conf['sep']);
echo "quote:\n";
File_CSV::_dbgBuff($conf['quote']);
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
fields: 3
sep:
buff: (,)
quote:
buff: (_NULL_)

Data:
Array
(
    [0] => Array
        (
            [0] => John
            [1] => Doe
            [2] => Bob
        )

    [1] => Array
        (
            [0] => John
            [1] => Doe
            [2] => Bob
        )

)
