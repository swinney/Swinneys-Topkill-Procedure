<?php   // -*- Mode: PHP; indent-tabs-mode: nil; -*-

require_once("PEAR.php");

class Swinsite_Persistent_DBPeer extends PEAR {
    public mixed $connection = null;

    public function __construct() {
        parent::__construct();
    }

    // accessor methods

    public function connection(): mixed {
        if (!$this->connection) {
            global $SWINSITE;

            $tmp = $SWINSITE['db_connection'];
            if (!$tmp) {
                return $this->raiseError("no db connection");
            }

            $this->connection = $tmp;
        }

        return $this->connection;
    }

    // persistence methods

    public function select(mixed &$obj): mixed {
        $query = $this->get_select_sql($obj);
        if (PEAR::isError($query)) {
            return $query;
        }

        $connection = $this->connection();
        if (PEAR::isError($connection)) {
            return $connection;
        }

        $row = $connection->getRow($query);
        if (PEAR::isError($row)) {
            return $row;
        }
        if (!$row) {
            return PERSISTENT_ERROR_NOT_FOUND;
        }

        $rv = $this->fill_obj($obj, $row);
        if (PEAR::isError($rv) || $rv != PERSISTENT_OK) {
            return $rv;
        }

        return PERSISTENT_OK;
    }

    public function insert(mixed $obj): mixed {
        $query = $this->get_insert_sql($obj);
        if (!$query) {
            return PERSISTENT_ERROR_BAD_REQUEST;
        }

        $connection = $this->connection();
        $rv = $connection->query($query);
        if (PEAR::isError($rv)) {
            return $rv;
        }

        // XXX: is there a better portable way of retrieving the id?

        $query = $this->get_last_insert_id_sql();
        if (!$query) {
            return PERSISTENT_ERROR_BAD_REQUEST;
        }

        $id = $connection->getOne($query);
        if (PEAR::isError($id)) {
            /*
             * XXX: how to correctly handle? the insert was
             * successful, but discovering the new id was not
             */
            return $id;
        }

        $obj->id = $id;

        return PERSISTENT_OK;
    }

    public function update(mixed $obj): mixed {
        $query = $this->get_update_sql($obj);
        if (!$query) {
            return PERSISTENT_ERROR_BAD_REQUEST;
        }

        $connection = $this->connection();
        $rv = $connection->query($query);
        if (PEAR::isError($rv)) {
            return $rv;
        }

        return PERSISTENT_OK;
    }

    public function delete(mixed $obj): mixed {
        $query = $this->get_delete_sql($obj);
        if (!$query) {
            return PERSISTENT_ERROR_BAD_REQUEST;
        }

        $connection = $this->connection();
        $rv = $connection->query($query);
        if (PEAR::isError($rv)) {
            return $rv;
        }

        return PERSISTENT_OK;
    }
}

?>
