<?php   // -*- Mode: PHP; indent-tabs-mode: nil; -*-

require_once("PEAR.php");

class Swinsite_Persistent_DBSetPeer extends PEAR {
    var $connection;

    // accessor methods

    function connection() {
        if (! $this->connection) {
            global $SWINSITE;

            $tmp = $SWINSITE['db_connection'];
            if (! $tmp) {
                return $this->raiseError("no db connection");
            }

            $this->connection = $tmp;
        }

        return $this->connection;
    }

    // persistence methods

    function select($set) {
        $query = $this->get_select_sql($set);
        if (PEAR::isError($query)) {
            return $query;
        }

        $connection = $this->connection();
        if (PEAR::isError($connection)) {
            return $connection;
        }

        $rows = $connection->getAll($query);
        if (PEAR::isError($row)) {
            return $row;
        }

        $list = array();
        foreach ($rows as $row) {
            $obj = $this->fill_obj($row);
            if (PEAR::isError($obj)) {
                return $obj;
            }

            array_push($list, $obj);
        }

        return $list;
    }

    function insert($set, $obj) {
        $query = $this->get_insert_sql($set, $obj);
        if (! $query) {
            return PERSISTENT_ERROR_BAD_REQUEST;
        }

        $connection = $this->connection();
        $rv = $connection->query($query);
        if (PEAR::isError($rv)) {
            return $rv;
        }

        return PERSISTENT_OK;
    }

    function delete($set, $obj) {
        $query = $this->get_delete_sql($set, $obj);
        if (! $query) {
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
