<?php
/*
 * $Id$
 */

class WebAddress {

    function checkWeb($web) {
        if (ereg("@",$web) && !ereg("mailto",$web)) {
            $web="mailto:$web";
        }
        if (!ereg("@",$web) && !ereg("http",$web)) {
            $web="http://$web";
        }
        return $web;
     }
}

?>
