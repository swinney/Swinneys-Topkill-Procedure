--TEST--
File_CSV Test Case bug14030: File_CSV::write() does not correctly quote field values
--FILE--
<?php
// $Id: bug14030.phpt,v 1.1 2008/09/21 21:17:49 dufuz Exp $
require 'File/CSV.php';

$rows = array(
    array(1, "I may be quoted", 1),
    array(2, "I \"must\" \"be\" quoted", 2),
    array(3, "   I must be quoted", 3),
    array(4, "I must be quoted   ", 4),
    array(5, "I must; \"be\"; quoted", 5),
    array(6, "I must\nbe\nquoted", 6),
);

$csv_conf = array(
    'fields' => 3,
    'crlf'   => "\r\n",
    'quote'  => '"',
    'sep'    => ';'
);

$csv_temp_filename = 'bug14030-to-delete.csv';
foreach ($rows as $csv_row) {
    $res = File_CSV::write($csv_temp_filename, $csv_row, $csv_conf);
}

echo file_get_contents($csv_temp_filename);
@unlink(dirname(__FILE__) . $csv_temp_filename);
?>
--EXPECT--
1;I may be quoted;1
2;"I ""must"" ""be"" quoted";2
3;"   I must be quoted";3
4;"I must be quoted   ";4
5;"I must; ""be""; quoted";5
6;"I must
be
quoted";6
