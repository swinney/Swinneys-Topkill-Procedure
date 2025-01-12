--TEST--
File_CSV Test Case bug13332: Excel dump, wrong field count in parsing, bug status Bogus
--FILE--
<?php
// $Id: bug13332.phpt,v 1.1 2008/09/21 21:17:19 dufuz Exp $

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/bug13332.csv';
$conf = array(
    'fields' => 5,
    'sep'    => ',',
    'quote'  => '"',
    'header' => 0
);

$cvs = array();
while (($tmp = File_CSV::read($file, $conf)) !== false) {
    $csv[] = $tmp;
}

var_dump($csv);
?>
--EXPECT--
array(2) {
  [0]=>
  array(5) {
    [0]=>
    string(1) "1"
    [1]=>
    string(1) "2"
    [2]=>
    string(6) "Twenty"
    [3]=>
    string(35) "This is a test of a "quoted" value."
    [4]=>
    string(15) "There is no cow"
  }
  [1]=>
  array(5) {
    [0]=>
    string(1) "2"
    [1]=>
    string(1) "4"
    [2]=>
    string(5) "Forty"
    [3]=>
    string(37) "Another "quoted value", with a comma."
    [4]=>
    string(14) "There is a cow"
  }
}
