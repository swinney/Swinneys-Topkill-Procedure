<?php
require_once 'File.php';
File::closeAll();
file_exists('test.txt') and unlink('test.txt');