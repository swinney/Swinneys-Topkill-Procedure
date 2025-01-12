--TEST--
File_CSV Test Case 006: One field quote autodiscovery
--FILE--
<?php
// $Id: 006.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 * - File_CSV::discoverFormat()
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/006.csv';
$conf = File_CSV::discoverFormat($file);

print "Format:\n";
print_r($conf);
print "\n";
?>
--EXPECT--
Format:
Array
(
    [fields] => 1
    [sep] => ,
    [quote] => "
)
