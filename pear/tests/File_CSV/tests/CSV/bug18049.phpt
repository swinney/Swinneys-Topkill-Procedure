--TEST--
File_CSV Test Case bug18049: discoverFormat bug, Find all seps that are within qoutes
--FILE--
<?php
// $Id: $
/**
 * Test for:
 * - File_CSV::discoverFormat()
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/bug18049.csv';
$conf = File_CSV::discoverFormat($file);
echo "Discovered fields: $conf[fields]\n";
echo "Format:\n";
print_r($conf);
?>
--EXPECT--
Discovered fields: 2
Format:
Array
(
    [fields] => 2
    [sep] => ;
    [quote] => "
)