<?php   // -*- Mode: PHP; indent-tabs-mode: nil; -*-

require_once("PEAR.php");
require_once("Swinsite/Persistent/Globals.php");

class Swinsite_Persistent_Object extends PEAR {
    var $id;
    var $isNew;
    var $isDirty;
    var $isDeleted;
    var $peer;

    function Swinsite_Persistent_Object($id=null) {
        $this->PEAR();

        if (isset($id)) {
            $this->id = $id;
            $this->isNew = 0;
            $this->isDirty = 0;
        } else {
            $this->isNew = 1;
            $this->isDirty = 1;
        }

        $this->isDeleted = 0;
    }

    // accessor methods

    function id($id=null) {
        if (isset($id)) {
            $this->id = $id;
            $this->isDirty = 1;
        }
        return $this->id;
    }

    // persistence methods

    function restore() {
        $peer = $this->peer();
        if (PEAR::isError($peer)) {
            return $peer;
        }

        $rv = $peer->select($this);
        if (PEAR::isError($rv) || $rv != PERSISTENT_OK) {
            return $rv;
        }

        $this->isNew = 0;
        $this->isDirty = 0;
        $this->isDeleted = 0;

        return $rv;
    }

    function save() {
        if (!($this->isDirty || $this->isDeleted)) {
            return PERSISTENT_OK;
        }

        $peer = $this->peer();
        if (PEAR::isError($peer)) {
            return $peer;
        }

        if ($this->isDeleted && !$this->isNew) {
            $rv = $peer->delete($this);
            if (PEAR::isError($rv) || $rv != PERSISTENT_OK) {
                return $rv;
            }

            $this->isNew = 1;
            $this->isDirty = 0;
            $this->isDeleted = 0;
        } else if ($this->isNew) {
            $rv = $peer->insert($this);
            if (PEAR::isError($rv) || $rv != PERSISTENT_OK) {
                return $rv;
            }

            $this->isNew = 0;
            $this->isDirty = 0;
            $this->isDeleted = 0;
        } else {
            $rv = $peer->update($this);
            if (PEAR::isError($rv) || $rv != PERSISTENT_OK) {
                return $rv;
            }

            $this->isNew = 0;
            $this->isDirty = 0;
            $this->isDeleted = 0;
        }

        return $rv;
    }

    function remove() {
        $this->isDeleted = 1;
        return $this->save();
    }
}

?>
