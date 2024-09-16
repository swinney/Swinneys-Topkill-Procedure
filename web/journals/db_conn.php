// Create a database connection
$db = DB::connect($_SESSION['dsn'], $options);
if (PEAR::isError($db)) {
    die('Database connection failed: ' . $db->getMessage());
}