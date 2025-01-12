<?php   // -*- Mode: PHP; indent-tabs-mode: nil; -*-

require_once("Bozos.php");
require_once("DBPeer/UserPeer.php");
require_once("Persistent/Object.php");

class Swinsite_User extends Swinsite_Persistent_Object {
    var $username;
    var $email;
    var $password;
    var $ip_addr;
    var $confidence;

    function Swinsite_User($id=null) {
        $this->Swinsite_Persistent_Object($id);
    }

    // accessor methods

    function username($username=null) {
        if (isset($username)) {
            $this->username = $username;
            $this->isDirty = 1;
        }
        return $this->username;
    }

    function email($email=null) {
        if (isset($email)) {
            $this->email = $email;
            $this->isDirty = 1;
        }
        return $this->email;
    }

    function password($password=null) {
        if (isset($password)) {
            $this->password = $password;
            $this->isDirty = 1;
        }
        return $this->password;
    }

    function ip_addr($ip_addr=null) {
        if (isset($ip_addr)) {
            $this->ip_addr = $ip_addr;
            $this->isDirty = 1;
        }
        return $this->ip_addr;
    }

    function confidence($confidence=null) {
        if (isset($confidence)) {
            $this->confidence = $confidence;
            $this->isDirty = 1;
        }
        return $this->confidence;
    }

    // public methods

    function bozos() {
        if (! $this->bozos) {
            $tmp = new Swinsite_Bozos($this->id());
            if (PEAR::isError($tmp)) {
                return $tmp;
            }

            $this->bozos = $tmp;
        }

        return $this->bozos;
    }

    // private methods

    function peer() {
        if (! $this->peer) {
            $this->peer = new Swinsite_DBPeer_UserPeer();
        }

        return $this->peer;
    }
}

?>
