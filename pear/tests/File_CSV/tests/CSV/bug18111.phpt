--TEST--
File_CSV Test Case bug18111: discoverFormat: Quote not detected in short lines
--FILE--
<?php
// $Id: $
/**
 * Test for:
 * - File_CSV::discoverFormat()
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/bug18111.csv';
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