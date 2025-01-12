<?php
session_start();

// Include configuration and functions
require_once 'login.inc.php'; // Assume this file contains necessary configurations

// Check if the user is already authenticated
if (isset($_SESSION['auth']['user_id'])) {
    // Redirect to a default page if already logged in
    header('Location: dashboard.php'); // Change this to your desired redirect page
    exit;
}

// Handle error messages if set
$error_msg = $_SESSION['error_msg'] ?? '';
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
    <!-- Include Google reCAPTCHA v2 script -->
    <script src="https://www.google.com/recaptcha/api.js" async defer></script>
</head>
<body>

<?php if ($error_msg): ?>
    <p style="color: red;"><strong><?= htmlspecialchars($error_msg); ?></strong></p>
<?php 
    // Clear the error message after displaying
    unset($_SESSION['error_msg']);
endif; 
?>

<!-- Begin login form -->
<form action="process_login.php" method="POST">
    <input type="hidden" name="back_to" value="<?= htmlspecialchars($_SESSION['back_to'] ?? '') ?>">
    <table cellpadding="2" cellspacing="0" border="0">
        <tr>
            <td align="right"><label for="username">Username:</label></td>
            <td><input type="text" name="username" id="username" size="25" maxlength="20" value="<?= htmlspecialchars($_SESSION['authenticated_username'] ?? '') ?>"></td>
        </tr>
        <tr>
            <td align="right"><label for="password">Password:</label></td>
            <td><input type="password" name="password" id="password" size="25" maxlength="20"></td>
        </tr>
        <tr>
            <td colspan="2">
                <!-- Display the reCAPTCHA widget -->
                <div class="g-recaptcha" data-sitekey="6LeIxAcTAAAAAJcZVRqyHh71UMIEGNQ_MXjiZKhI"></div>
            </td>
        </tr>
        <tr>
            <td>&nbsp;</td>
            <td><input type="submit" value="Log In"></td>
        </tr>
    </table>
</form>
<!-- End login form -->

</body>
</html>
