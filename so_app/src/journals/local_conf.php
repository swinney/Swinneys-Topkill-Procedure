<?php
define("URLBASE", getenv('URLBASE') ?: 'http://localhost'); // no trailing slash!
define("IMGURL", URLBASE ."/journals/images");
define("CSS_URL", URLBASE ."/journals/main.css");
define("HOME", "/app");
define("DIRBASE", HOME . "/journals");
define("IMGBASE", DIRBASE . "/images");
define("INCDIR", DIRBASE . "/templates");
define("LIBDIR", HOME . "/lib");

define("DB_USER", getenv('DB_USER') ?: 'not set');
define("DB_PASSWD", getenv('DB_PASSWD') ?: 'not set');
define("DB_NAME", getenv('DB_NAME') ?: 'not set');
define("DB_HOST", getenv('DB_HOST') ?: 'not set');
define("ERROR_REP", 1);
define("RECAPTCHA_SECRET_KEY", "6LeIxAcTAAAAAGG-vFI1TnRWxMZNFuojJ4WifJWe");
define('RECAPTCHA_SITE_KEY', '6LeIxAcTAAAAAJcZVRqyHh71UMIEGNQ_MXjiZKhI');

// Add this temporarily to debug
error_log("Environment variables:");
error_log("DB_HOST: " . (getenv('DB_HOST') ?: 'not set'));
error_log("DB_USER: " . (getenv('DB_USER') ?: 'not set'));
error_log("DB_NAME: " . (getenv('DB_NAME') ?: 'not set'));
error_log("DB_PASSWD exists: " . (getenv('DB_PASSWD') ? 'yes' : 'no'));

?>
