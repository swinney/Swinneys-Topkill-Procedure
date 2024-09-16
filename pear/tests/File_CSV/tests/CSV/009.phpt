--TEST--
File_CSV Test Case 009: Escaping of quotes within quotes.
--FILE--
<?php
// $Id: 009.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 * - parsing, how we handle quotes and separators inside quotes
 *   and empty fields
 * data gotten from http://www.creativyst.com/Doc/Articles/CSV/CSV01.htm
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/009.csv';
$conf = File_CSV::discoverFormat($file);

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
            [0] => John "Da Man"
            [1] => Repici
            [2] => 120 Jefferson St.
            [3] => Riverside
            [4] => NJ
            [5] => 08075
        )

    [1] => Array
        (
            [0] => Stephen
            [1] => Tyler
            [2] => 7452 Terrace "At the Plaza" road
            [3] => SomeTown
            [4] => SD
            [5] => 91234
        )

    [2] => Array
        (
            [0] => John "Da Man"
            [1] => Repici
            [2] => 120 Jefferson St.
            [3] => Riverside
            [4] => NJ
            [5] => 08075
        )

    [3] => Array
        (
            [0] => Repici
            [1] => John "Da Man"
            [2] => 120 Jefferson St.
            [3] => Riverside
            [4] => NJ
            [5] => 08075
        )

)
