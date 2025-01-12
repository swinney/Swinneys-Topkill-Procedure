<?php
/*
 * $Id$
 */

class WebAddress {

    function checkWeb($web) {
        if (strpos($web, "@") !== false && strpos($web, "mailto") === false) {
            $web = "mailto:$web";
        }
        if (strpos($web, "@") === false && strpos($web, "http") === false) {
            $web = "http://$web";
        }
        return $web;
     }
}

?>
