<?php   // -*- Mode: PHP; indent-tabs-mode: nil; -*-

require_once("Swinsite/Persistent/DBSetPeer.php");
require_once("Swinsite/Persistent/Globals.php");
require_once("Swinsite/User.php");

class Swinsite_DBPeer_BozosPeer extends Swinsite_Persistent_DBSetPeer {

    // persistence methods

    function fill_obj($row) {
        $bozo = new Swinsite_User($row[0]);
        $bozo->username = stripslashes($row[1]);
        $bozo->email = stripslashes($row[2]);
        $bozo->password = stripslashes($row[3]);
        $bozo->ip_addr = stripslashes($row[4]);
        $bozo->confidence = $row[5];

        return $bozo;
    }

    function get_select_sql($set) {
        $id = $set->id();

        return <<<EOT
  SELECT u.user_id, u.username, u.email, u.password, u.ip_addr, u.confidence
    FROM user AS u,
         user_bozo AS b
   WHERE b.bozo_id=u.user_id
     AND b.user_id=$id
EOT;
    }

    function get_insert_sql($set, $bozo) {
        $set_id = $set->id();
        $bozo_id = $bozo->id();
        $username = addslashes($bozo->username());

        return <<<EOT
INSERT INTO user_bozo
     VALUES ($set_id, $bozo_id, '$username')
EOT;
    }

    function get_delete_sql($set, $bozo) {
        $set_id = $set->id();
        $bozo_id = $bozo->id();

        return <<<EOT
  DELETE from user_bozo
   WHERE user_id=$set_id
     AND bozo_id=$bozo_id
EOT;
    }
}

?>
