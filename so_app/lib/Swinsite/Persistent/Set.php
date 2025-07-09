<?php   // -*- Mode: PHP; indent-tabs-mode: nil; -*-

require_once("PEAR.php");
require_once("Persistent/Globals.php");

class Swinsite_Persistent_Set extends PEAR {
    public ?int $id = null;
    public ?array $set = null;

    public function __construct(?int $id = null) {
        parent::__construct();

        if (isset($id)) {
            $this->id = $id;
        }
    }

    // accessor methods

    public function id(?int $id = null): ?int {
        if (isset($id)) {
            $this->id = $id;
        }
        return $this->id;
    }

    // persistence methods

    public function add(mixed $obj): mixed {
        $peer = $this->peer();
        if (PEAR::isError($peer)) {
            return $peer;
        }

        $rv = $peer->insert($this, $obj);
        if (PEAR::isError($rv)) {
            return $rv;
        }

        $this->set[] = $obj;

        return PERSISTENT_OK;
    }

    public function getAll(): mixed {
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

    public function remove(mixed $obj): mixed {
        $peer = $this->peer();
        if (PEAR::isError($peer)) {
            return $peer;
        }

        $rv = $peer->delete($this, $obj);
        if (PEAR::isError($rv)) {
            return $rv;
        }

        $tmp = [];
        $id = $obj->id();
        foreach ($this->set as $o) {
            if ($id != $o->id()) {
                $tmp[] = $o;
            }
        }
        $this->set = $tmp;

        return PERSISTENT_OK;
    }
}

?>
