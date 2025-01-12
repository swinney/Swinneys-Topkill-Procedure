<?php
// needed for locking test
define('FILE_LOCKS_BLOCK', false, true);
require_once 'File.php';

require_once dirname(__FILE__) . '/teardown.inc.php';

$str  = str_repeat(str_repeat("0123456789", 1000)."\n", 100);
$line = str_repeat("0123456789", 1000);

if (PEAR::isError($e = File::write('test.txt', $str, FILE_MODE_WRITE))) {
    die("Cannot start test: ". str_replace($str,'...', $e->getMessage()));
}