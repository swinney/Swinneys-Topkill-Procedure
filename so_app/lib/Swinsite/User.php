<?php   // -*- Mode: PHP; indent-tabs-mode: nil; -*-

require_once("Bozos.php");
require_once("DBPeer/UserPeer.php");
require_once("Persistent/Object.php");

class Swinsite_User extends Swinsite_Persistent_Object {
    public ?string $username = null;
    public ?string $email = null;
    public ?string $password = null;
    public ?string $ip_addr = null;
    public ?int $confidence = null;

    public function __construct(?int $id = null) {
        parent::__construct($id);
    }

    // accessor methods

    public function username(?string $username = null): ?string {
        if (isset($username)) {
            $this->username = $username;
            $this->isDirty = 1;
        }
        return $this->username;
    }

    public function email(?string $email = null): ?string {
        if (isset($email)) {
            $this->email = $email;
            $this->isDirty = 1;
        }
        return $this->email;
    }

    public function password(?string $password = null): ?string {
        if (isset($password)) {
            $this->password = $password;
            $this->isDirty = 1;
        }
        return $this->password;
    }

    public function ip_addr(?string $ip_addr = null): ?string {
        if (isset($ip_addr)) {
            $this->ip_addr = $ip_addr;
            $this->isDirty = 1;
        }
        return $this->ip_addr;
    }

    public function confidence(?int $confidence = null): ?int {
        if (isset($confidence)) {
            $this->confidence = $confidence;
            $this->isDirty = 1;
        }
        return $this->confidence;
    }

    // public methods

    public function bozos(): Swinsite_Bozos {
        if (!$this->bozos) {
            $tmp = new Swinsite_Bozos($this->id());
            if (PEAR::isError($tmp)) {
                return $tmp;
            }

            $this->bozos = $tmp;
        }

        return $this->bozos;
    }

    // private methods

    public function peer(): Swinsite_DBPeer_UserPeer {
        if (!$this->peer) {
            $this->peer = new Swinsite_DBPeer_UserPeer();
        }

        return $this->peer;
    }
}

?>
