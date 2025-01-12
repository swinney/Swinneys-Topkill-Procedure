<?php

require_once './global.php'; // Include necessary configurations (database connection, reCAPTCHA function)

$dsn = $_SESSION['dsn'];
// Create a database connection
$db = DB::connect($_SESSION['dsn'], $options);
if (PEAR::isError($db)) {
    die('Database connection failed: ' . $db->getMessage());
}

class Registration
{
    private $db;
    private $recaptchaSecret;

    public function __construct($db, $recaptchaSecret)
    {
        $this->db = $db;
        $this->recaptchaSecret = $recaptchaSecret;
    }

    /**
     * Validate the registration form data.
     */
    public function validateForm($email, $password, $captchaResponse)
    {
        // Validate the email address
        if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
            throw new Exception("Invalid email address.");
        }

        // Validate the password
        if (!$this->validatePassword($password)) {
            throw new Exception("Password must be at least 8 characters long, contain at least one uppercase letter, one lowercase letter, one number, and one special character.");
        }

        // Validate the CAPTCHA response
        if (!$this->validateCaptcha($captchaResponse)) {
            throw new Exception("CAPTCHA verification failed. Please try again.");
        }
    }

    /**
     * Check if the password meets the complexity requirements.
     */
    private function validatePassword($password)
    {
        $pattern = "/^(?=.*[A-Z])(?=.*[a-z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$/";
        return preg_match($pattern, $password);
    }

    /**
     * Validate reCAPTCHA v2 response.
     */
    private function validateCaptcha($captchaResponse)
    {
        $response = file_get_contents(
            "https://www.google.com/recaptcha/api/siteverify?secret={$this->recaptchaSecret}&response={$captchaResponse}"
        );
        $responseKeys = json_decode($response, true);
        return $responseKeys['success'];
    }

    /**
     * Register a new user.
     */
    public function registerUser($username, $email, $password, $ip_addr, $city, $state, $country)
    {
        // Hash the password securely
        $hashedPassword = password_hash($password, PASSWORD_BCRYPT);

        // Prepare and execute the query using PEAR::DB
        $query = "INSERT INTO user (username, email, password, ip_addr, city, state, country) 
                  VALUES (?, ?, ?, ?, ?, ?, ?)";
        $stmt = $this->db->prepare($query);

        if (DB::isError($stmt)) {
            throw new Exception("Database error: Could not prepare statement.");
        }

        $result = $this->db->execute($stmt, array($username, $email, $hashedPassword, $ip_addr, $city, $state, $country));

        if (DB::isError($result)) {
            throw new Exception("Database error: " . $result->getMessage());
        }

        return $result;
    }
}

// Make sure the request is a POST request
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    try {
        // Initialize the Registration object
        $registration = new Registration($db, RECAPTCHA_SECRET_KEY);

        // Collect input data
        $username = $_POST['username'] ?? '';
        $email = $_POST['email'] ?? '';
        $password = $_POST['password'] ?? '';
        $captchaResponse = $_POST['g-recaptcha-response'] ?? '';

        // Simulate getting the user's IP address and location data (city, state, country)
        $ip_addr = $_SERVER['REMOTE_ADDR'] ?? '127.0.0.1';
        $city = 'Elko';
        $state = 'Nevada';
        $country = 'US';

        // Validate the form
        $registration->validateForm($email, $password, $captchaResponse);

        // Register the user
        if ($registration->registerUser($username, $email, $password, $ip_addr, $city, $state, $country)) {
            echo "User registered successfully.";
        } else {
            throw new Exception("Registration failed.");
        }
    } catch (Exception $e) {
        // Handle exceptions and provide meaningful feedback to the user
        echo "Error: " . $e->getMessage();
    }
}
?>

