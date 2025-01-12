--TEST--
File_CSV Test Case bug5257-2: Delimiter problem if first field is empty
--FILE--
<?php
// $Id: bug5257-2.phpt,v 1.1 2008/09/21 21:15:44 dufuz Exp $
/**
 * Test for:
 * - File_CSV::readQuoted()
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/bug5257-2.csv';
$conf = File_CSV::discoverFormat($file);
echo "Discovered fields: $conf[fields]\n";
echo "Format:\n";
for ($idx = 0; $idx < 3; ++$idx) {
    print_r(File_CSV::readQuoted($file, $conf));
    echo "\n";
}
?>
--EXPECT--
Discovered fields: 2
Format:
Array
(
    [0] => 
    [1] => Snargleblarg
)

Array
(
    [0] => 
    [1] => OTA
)

Array
(
    [0] => 
    [1] => bloa acvnb
)
