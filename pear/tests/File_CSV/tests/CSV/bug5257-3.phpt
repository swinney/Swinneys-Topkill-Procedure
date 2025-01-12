--TEST--
File_CSV Test Case bug5257-3: Delimiter problem if first field is empty
--FILE--
<?php
// $Id: bug5257-3.phpt,v 1.1 2008/09/21 21:15:44 dufuz Exp $
/**
 * Test for:
 * - File_CSV::readQuoted()
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/bug5257-3.csv';
$conf = File_CSV::discoverFormat($file);
echo "Discovered fields: $conf[fields]\n";
echo "Format:\n";
while ($row = File_CSV::readQuoted($file, $conf)) {
    print_r($row);
    echo "\n";
}
?>
--EXPECT--
Discovered fields: 5
Format:
Array
(
    [0] => Field 0
    [1] => Field 1
    [2] => Field 2
    [3] => Field 3
    [4] => Field 4
)

Array
(
    [0] => 
    [1] => Field 1
    [2] => 
    [3] => Field 3
    [4] => 
)
