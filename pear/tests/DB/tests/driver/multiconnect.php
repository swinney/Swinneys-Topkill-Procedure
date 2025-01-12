<?php

/**
 * Tests the various ways DB's connect() function operates
 *
 * PHP version 5
 *
 * LICENSE: This source file is subject to version 3.0 of the PHP license
 * that is available through the world-wide-web at the following URI:
 * http://www.php.net/license/3_0.txt.  If you did not receive a copy of
 * the PHP License and are unable to obtain it through the web, please
 * send a note to license@php.net so we can mail you a copy immediately.
 *
 * @category   Database
 * @package    DB
 * @author     Daniel Convissor <danielc@php.net>
 * @copyright  1997-2007 The PHP Group
 * @license    http://www.php.net/license/3_0.txt  PHP License 3.0
 * @version    $Id$
 * @link       http://pear.php.net/package/DB
 * @since      File available since Release 1.7.0
 */

/**
 * Establish the include_path, DSN's and connection $options
 */
require_once dirname(__FILE__) . '/setup.inc';

foreach ($dsns as $dbms => $dsn) {
    echo "======== $dbms ========\n";
    $options['persistent'] = false;
    $dbh = DB::connect($dsn, $options);
    if (DB::isError($dbh)) {
        echo 'PROBLEM: ' . $dbh->getUserInfo() . "\n";
        continue;
    }

    if ($dbh->provides('new_link')
        && version_compare(phpversion(), $dbh->provides('new_link'), '>='))
    {
        $probs = false;
        $dsn = DB::parseDSN($dsn);
        $dsn['new_link'] = true;
        $dbh = DB::connect($dsn, $options);
        if (DB::isError($dbh)) {
            echo 'NEW LINK PROBLEM: ' . $dbh->getUserInfo() . "\n";
            $probs = true;
        }

        if ($dbh->provides('pconnect')) {
            $options['persistent'] = true;
            $dbh->disconnect();
            $dbh = DB::connect($dsn, $options);
            if (DB::isError($dbh)) {
                echo 'PERSIST NEWCON PROBLEM: ' . $dbh->getUserInfo() . "\n";
                $probs = true;
            }

            unset($dsn['new_link']);
            $dbh->disconnect();
            $dbh = DB::connect($dsn, $options);
            if (DB::isError($dbh)) {
                echo 'PERSIST OLDCON PROBLEM: ' . $dbh->getUserInfo() . "\n";
                $probs = true;
            }
        }
        if ($probs) {
            continue;
        }
        $dbh->disconnect();

    } elseif ($dbh->provides('pconnect')) {
        $options['persistent'] = true;
        $dbh->disconnect();
        $dbh = DB::connect($dsn, $options);
        if (DB::isError($dbh)) {
            echo 'PERSIST PROBLEM: ' . $dbh->getUserInfo() . "\n";
            continue;
        }
        $dbh->disconnect();
    }
    echo "GOOD\n";
}
