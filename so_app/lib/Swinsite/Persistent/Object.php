<?php   // -*- Mode: PHP; indent-tabs-mode: nil; -*-

require_once("PEAR.php");
require_once("Persistent/Globals.php");

class Swinsite_Persistent_Object extends PEAR {
    public ?int $id = null;
    public int $isNew = 0;
    public int $isDirty = 0;
    public int $isDeleted = 0;
    public mixed $peer = null;

    public function __construct(?int $id = null) {
        parent::__construct();

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

    public function id(?int $id = null): ?int {
        if (isset($id)) {
            $this->id = $id;
            $this->isDirty = 1;
        }
        return $this->id;
    }

    // persistence methods

    public function restore(): mixed {
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

    public function save(): mixed {
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
        } elseif ($this->isNew) {
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

    public function remove(): mixed {
        $this->isDeleted = 1;
        return $this->save();
    }
}

?>
