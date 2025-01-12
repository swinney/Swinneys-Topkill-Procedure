--TEST--
File_Util::buildPath()
--FILE--
<?php
// $Id: $
require_once 'File/Util.php';

$path = array(
    'some',
    DIRECTORY_SEPARATOR,
    DIRECTORY_SEPARATOR,
    DIRECTORY_SEPARATOR,
    DIRECTORY_SEPARATOR,
    'weird'.DIRECTORY_SEPARATOR,
    DIRECTORY_SEPARATOR,
    DIRECTORY_SEPARATOR,
    DIRECTORY_SEPARATOR,
    DIRECTORY_SEPARATOR.'path'.DIRECTORY_SEPARATOR.DIRECTORY_SEPARATOR,
);

$built = implode(DIRECTORY_SEPARATOR, array('some','weird','path','',''));
var_dump($built === File_Util::buildPath($path));
?>
--EXPECT--
bool(true)