<?php   // -*- Mode: PHP; indent-tabs-mode: nil; -*-

require_once("Swinsite/Persistent/DBPeer.php");
require_once("Swinsite/Persistent/Globals.php");

class Swinsite_DBPeer_UserPeer extends Swinsite_Persistent_DBPeer {

    function Swinsite_DBPeer_UserPeer() {
        $this->Swinsite_Persistent_DBPeer();
    }

    // persistence methods

    function fill_obj($obj, $row) {
        $obj->id = $row[0];
        $obj->username = stripslashes($row[1]);
        $obj->email = stripslashes($row[2]);
        $obj->password = stripslashes($row[3]);
        $obj->ip_addr = stripslashes($row[4]);
        $obj->confidence = $row[5];

        return PERSISTENT_OK;
    }

    function get_select_sql($obj) {
        $query = <<<EOT
  SELECT user_id, username, email, password, ip_addr, confidence
    FROM user
   WHERE 
EOT;

        $args = array();
        if (isset($obj->id)) {
            array_push($args, "user_id=$obj->id");
        }
        if (isset($obj->username)) {
            array_push($args, "username='$obj->username'");
        }
        if (isset($obj->email)) {
            array_push($args, "email='$obj->email'");
        }
        if (isset($obj->password)) {
            array_push($args, "password='$obj->password'");
        }
        if (isset($obj->ip_addr)) {
            array_push($args, "ip_addr='$obj->ip_addr'");
        }
        if (isset($obj->confidence)) {
            array_push($args, "confidence=$obj->confidence");
        }

        if (count($args) <= 0) {
            return $this->raiseError("no fields to select on", null,
                                     null, null, $query);
        }

        return ($query . implode($args, " AND "));
    }

    function get_insert_sql($obj) {
        $username = addslashes($obj->username());
        $email = addslashes($obj->email());
        $password = addslashes($obj->password());
        $ip_addr = addslashes($obj->ip_addr());
        $confidence = $obj->confidence();

        return <<<EOT
INSERT INTO user
     VALUES (NULL, '$username', '$email', '$password', '$ip_addr', $confidence)
EOT;
    }

    function get_update_sql($obj) {
        $id = $obj->id();
        $username = addslashes($obj->username());
        $email = addslashes($obj->email());
        $password = addslashes($obj->password());
        $ip_addr = addslashes($obj->ip_addr());
        $confidence = $obj->confidence();

        return <<<EOT
UPDATE user
   SET username='$username',
       email='$email',
       password='$password',
       ip_addr='$ip_addr',
       confidence=$confidence
 WHERE user_id=$id
EOT;
    }

    function get_delete_sql($obj) {
        $id = $obj->id();

        return <<<EOT
DELETE FROM user
      WHERE user_id=$id
EOT;
}

    function get_last_insert_id_sql() {
        return <<<EOT
  SELECT id
    FROM user
ORDER BY id DESC
   LIMIT 1
EOT;
    }
}

?>




