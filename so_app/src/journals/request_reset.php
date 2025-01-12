<?php
require_once 'global.php'; // Include the database connection and utilities
require_once 'db_conn.php'; // Include PEAR::DB

class PasswordReset
{
    private $db;

    public function __construct($db)
    {
        $this->db = $db;
    }

    /**
     * Send a password reset email to the user.
     */
    public function requestPasswordReset($email)
    {
        // Check if the email exists in the database
        $query = "SELECT user_id FROM user WHERE email = ?";
        $stmt = $this->db->prepare($query);

        if (DB::isError($stmt)) {
            throw new Exception("Database error: Could not prepare statement.");
        }

        $result = $this->db->execute($stmt, array($email));
        $user = $result->fetchRow();

        if (!$user) {
            throw new Exception("No user found with this email address.");
        }

        // Generate a unique reset token
        $token = bin2hex(random_bytes(32));
        $expiry = new DateTime();
        $expiry->add(new DateInterval('PT1H')); // Token valid for 1 hour

        // Store the token and expiry in the database
        $query = "UPDATE user SET password_reset_token = ?, token_expiry = ? WHERE email = ?";
        $stmt = $this->db->prepare($query);

        if (DB::isError($stmt)) {
            throw new Exception("Database error: Could not prepare statement.");
        }

        $result = $this->db->execute($stmt, array($token, $expiry->format('Y-m-d H:i:s'), $email));

        if (DB::isError($result)) {
            throw new Exception("Database error: Could not update token.");
        }

        // Send the password reset email
        $this->sendResetEmail($email, $token);
    }

    /**
     * Send the reset email to the user.
     */
    private function sendResetEmail($email, $token)
    {
        $resetLink = "http://swinney.org/reset_password.php?token=" . $token;
        $subject = "Password Reset Request";
        $message = "Click the following link to reset your password: " . $resetLink;
        $headers = "From: no-reply@yourdomain.com";

        // Send the email
        mail($email, $subject, $message, $headers);
    }
}

// Handle the password reset request form submission
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    try {
        // Initialize PEAR::DB connection
        $dsn = $_SESSION['dsn'];
        $db = DB::connect($dsn);

        if (DB::isError($db)) {
            die($db->getMessage());
        }

        // Get the email from the POST request
        $email = $_POST['email'] ?? '';

        // Initialize the PasswordReset object
        $reset = new PasswordReset($db);
        $reset->requestPasswordReset($email);

        echo "Password reset email sent.";
    } catch (Exception $e) {
        echo "Error: " . $e->getMessage();
    }
}
?>

<!-- HTML form for password reset request -->
<form action="request_reset.php" method="POST">
    <label for="email">Enter your email to reset your password:</label>
    <input type="email" name="email" required>
    <input type="submit" value="Send Password Reset Email">
</form>
