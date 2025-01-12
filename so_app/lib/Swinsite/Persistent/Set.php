<?php   // -*- Mode: PHP; indent-tabs-mode: nil; -*-

require_once("PEAR.php");
require_once("Persistent/Globals.php");

class Swinsite_Persistent_Set extends PEAR {
    var $id;
    var $set;

    function Swinsite_Persistent_Set($id=null) {
        $this->PEAR();

        if (isset($id)) {
            $this->id = $id;
        }
    }

    // accessor methods

    function id($id=null) {
        if (isset($id)) {
            $this->id = $id;
        }
        return $this->id;
    }

    // persistence methods

    function add($obj) {
        $peer = $this->peer();
        if (PEAR::isError($peer)) {
            return $peer;
        }

        $rv = $peer->insert($this, $obj);
        if (PEAR::isError($rv)) {
            return $rv;
        }

        array_push($this->set, $obj);

        return PERSISTENT_OK;
    }

    function getAll() {
        if (isset($this->set)) {
            return $this->set;
        }

        $peer = $this->peer();
        if (PEAR::isError($peer)) {
            return $peer;
        }

        $tmp = $peer->select($this);
        if (PEAR::isError($tmp)) {
            return $tmp;
        }

        $this->set = $tmp;
        return $this->set;
    }

    function remove($obj) {
        $peer = $this->peer();
        if (PEAR::isError($peer)) {
            return $peer;
        }

        $rv = $peer->delete($this, $obj);
        if (PEAR::isError($rv)) {
            return $rv;
        }

        $tmp = array();
        $id = $obj->id();
        foreach ($this->set as $o) {
            if ($id != $o->id()) {
                array_push($tmp, $o);
            }
        }
        $this->set = $tmp;

        return PERSISTENT_OK;
    }
}

?>
