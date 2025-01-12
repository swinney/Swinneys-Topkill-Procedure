--TEST--
File_CSV Test Case 015: Various different lines.
--FILE--
<?php
// $Id: 015.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 * - parsing, how we handle quotes and separators inside quotes
 *   and empty fields
 * data gotten from http://www.creativyst.com/Doc/Articles/CSV/CSV01.htm
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/015.csv';
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
            [0] => John
            [1] => Doe
            [2] => 120 jefferson st.
            [3] => Riverside
            [4] => NJ
            [5] => 08075
        )

    [1] => Array
        (
            [0] => Jack
            [1] => McGinnis
            [2] => 220 hobo Av.
            [3] => Phila
            [4] => PA
            [5] => 09119
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
            [0] => Stephen
            [1] => Tyler
            [2] => 7452 Terrace "At the Plaza" road
            [3] => SomeTown
            [4] => SD
            [5] => 91234
        )

    [4] => Array
        (
            [0] => 
            [1] => Blankman
            [2] => 
            [3] => SomeTown
            [4] => SD
            [5] => 00298
        )

)
