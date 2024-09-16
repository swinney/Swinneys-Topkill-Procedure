--TEST--
File_CSV Test Case bug4792_part1: All lines but last end with a whitespace Part 1
--FILE--
<?php
// $Id: bug4792_part1.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 *   - odd quote behaviour in discoverFormat excludes the last field
 *     When the first field is quoted and the next field is not then
 *     the last field is popped off
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/bug4792_part1.csv';
$conf = File_CSV::discoverFormat($file);

echo "Data:\n";
while ($row = File_CSV::read($file, $conf)) {
    $lastColumn = $row[count($row)-1];
    echo str_replace("\r\n","[CRLF]", $lastColumn);
    echo ($lastColumn == trim($lastColumn)) ? '- Ends OK' : '- Ends with white space';
    echo "\n";
}

?>
--EXPECT--
Data:
Email- Ends OK
razzar@gmail.com- Ends OK
email@email.com- Ends OK
