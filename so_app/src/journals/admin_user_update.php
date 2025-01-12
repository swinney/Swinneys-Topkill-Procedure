<?php
require_once 'global.php'; // Assume this file initializes the $db connection using PEAR::DB

$dsn = $_SESSION['dsn'];
// Create a database connection
$db = DB::connect($_SESSION['dsn'], $options);
if (PEAR::isError($db)) {
    die('Database connection failed: ' . $db->getMessage());
}


class AdminUserUpdate
{
    private $db;

    public function __construct($db)
    {
        $this->db = $db;
    }

    /**
     * Updates the user's password and/or email based on the given username.
     *
     * @param string $username The username of the user to update.
     * @param string|null $newPassword The new password (optional).
     * @param string|null $newEmail The new email (optional).
     * @return string A message indicating the result of the operation.
     * @throws Exception if an error occurs during the update process.
     */
    public function updateUser($username, $newPassword = null, $newEmail = null)
    {
        // Prepare fields to update
        $fieldsToUpdate = [];
        $params = [];

        // Hash the password if provided
        if (!empty($newPassword)) {
            $hashedPassword = password_hash($newPassword, PASSWORD_BCRYPT);
            $fieldsToUpdate[] = "password = ?";
            $params[] = $hashedPassword;
        }

        // Update email if provided
        if (!empty($newEmail)) {
            if (!filter_var($newEmail, FILTER_VALIDATE_EMAIL)) {
                throw new Exception("Invalid email format.");
            }
            $fieldsToUpdate[] = "email = ?";
            $params[] = $newEmail;
        }

        // If no fields are provided to update, throw an error
        if (empty($fieldsToUpdate)) {
            throw new Exception("Nothing changed.");
        }

        // Add the username to the query parameters
        $params[] = $username;

        // Construct the SQL query dynamically based on which fields are being updated
        $query = "UPDATE user SET " . implode(", ", $fieldsToUpdate) . " WHERE username = ?";
        $stmt = $this->db->prepare($query);

        if (DB::isError($stmt)) {
            throw new Exception("Database error: Could not prepare the statement.");
        }

        // Execute the query
        $result = $this->db->execute($stmt, $params);

        if (DB::isError($result)) {
            throw new Exception("Database error: Could not execute the update.");
        }

        return "User's information updated successfully.";
    }
}

// Process form submission
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    try {
        // Retrieve POST data
        $username = $_POST['username'] ?? '';
        $newPassword = $_POST['password'] ?? null;
        $newEmail = $_POST['email'] ?? null;

        // Validate that the username is provided
        if (empty($username)) {
            throw new Exception("Username is required.");
        }

        // Initialize the AdminUserUpdate class
        $userUpdate = new AdminUserUpdate($db);

        // Perform the update
        $message = $userUpdate->updateUser($username, $newPassword, $newEmail);

        // Set success message
        $successMessage = $message;
    } catch (Exception $e) {
        // Catch and display errors
        $errorMessage = $e->getMessage();
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Admin - Update User Information</title>
</head>
<body>

<!-- Display success or error messages -->
<?php if (isset($successMessage)): ?>
    <p style="color: green;"><?= htmlspecialchars($successMessage); ?></p>
<?php elseif (isset($errorMessage)): ?>
    <p style="color: red;"><?= htmlspecialchars($errorMessage); ?></p>
<?php endif; ?>

<!-- Form for updating user's password and email -->
<form action="admin_user_update.php" method="POST">
    <label for="username">Username:</label>
    <input type="text" name="username" id="username" required><br>

    <label for="password">New Password:</label>
    <input type="password" name="password" id="password"><br>

    <label for="email">New Email:</label>
    <input type="email" name="email" id="email"><br>

    <input type="submit" value="Update User">
</form>

</body>
</html>
