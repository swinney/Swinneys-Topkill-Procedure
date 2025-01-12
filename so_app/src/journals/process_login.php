<?php
require_once './global.php'; // Include global configurations
// Create a database connection
$dsn = $_SESSION['dsn'];
$db = DB::connect($_SESSION['dsn'], $options);
if (PEAR::isError($db)) {
    die('Database connection failed: ' . $db->getMessage());
}

// Check if the user is already authenticated
if (isset($_SESSION['auth']['user_id'])) {
    header('Location: index.php'); // Redirect to a logged-in page
    exit;
}
// Collect form inputs
$username = $_POST['username'] ?? '';
$password = $_POST['password'] ?? '';
$recaptchaResponse = $_POST['g-recaptcha-response'] ?? '';
$back_to = $_POST['back_to'] ?? 'index.php'; // Default redirect

// Validate reCAPTCHA v2 response
if (!validateRecaptcha($recaptchaResponse)) {
    $_SESSION['error_msg'] = 'CAPTCHA verification failed. Please try again.';
    header('Location: login.php');
    exit;
}

// Check if the username and password are provided
if (empty($username) || empty($password)) {
    $_SESSION['error_msg'] = 'Username and password are required.';
    header('Location: login.php');
    exit;
}
// Query to fetch the user
$user = $db->getRow("SELECT user_id, username, password FROM user WHERE username = ?", [$username], DB_FETCHMODE_ASSOC);
if (PEAR::isError($user) || empty($user)) {
    $_SESSION['error_msg'] = 'Invalid username or password.';
    header('Location: login.php');
    exit;
}

// Verify password
if (password_verify($password, $user['password'])) {
    // Set session variables
    $_SESSION['authenticated_user_id'] = $user['user_id'];
    $_SESSION['authenticated_username'] = $user['username'];
    $_SESSION['auth']['user_id'] = $_SESSION['authenticated_user_id'];
    $_SESSION['auth']['username'] = $_SESSION['authenticated_username'];

    // Set cookies for session persistence (if needed)
    setcookie("authenticated_user_id", $_SESSION['authenticated_user_id'], [
        'expires' => time() + 1296000, // 15 days
        'path' => '/',
        'domain' => 'swinney.org',
        'secure' => true, // Only send over HTTPS
        'httponly' => true, // Not accessible via JavaScript
        'samesite' => 'Lax', // CSRF protection
    ]);

    setcookie("authenticated_username", $_SESSION['authenticated_username'], [
        'expires' => time() + 1296000, // 15 days
        'path' => '/',
        'domain' => 'swinney.org',
        'secure' => true, // Only send over HTTPS
        'httponly' => true, // Not accessible via JavaScript
        'samesite' => 'Lax', // CSRF protection
    ]);

    // Redirect to the original page or a default one
    header("Location: $back_to");
    exit;
} else {
    $_SESSION['error_msg'] = 'Sess. Invalid username or password.';
    header('Location: login.php');
    exit;
}
?>
