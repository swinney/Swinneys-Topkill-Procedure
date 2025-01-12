<?php   // -*- Mode: PHP; indent-tabs-mode: nil; -*-

require_once("DBPeer/BozosPeer.php");
require_once("Persistent/Set.php");

class Swinsite_Bozos extends Swinsite_Persistent_Set {
    var $bozos;

    // private methods

    function peer() {
        if (! $this->peer) {
            $this->peer = new Swinsite_DBPeer_BozosPeer();
        }

        return $this->peer;
    }
}

?>
