--TEST--
File_CSV Test Case bug11526: Fields count less than expected
--FILE--
<?php
// $Id: bug11526.phpt,v 1.2 2008/09/21 21:25:58 dufuz Exp $
require_once 'File/CSV.php';
$path = dirname(__FILE__) . '/bug11526.csv';
$conf = File_CSV::discoverFormat($path);
echo $conf['fields'];
?>
--EXPECT--
12