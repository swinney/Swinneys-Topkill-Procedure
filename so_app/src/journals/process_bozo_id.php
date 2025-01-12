<?php
require_once("global.php");

if (!isset($uid)) {
    $_SESSION['error_msg'] = "<p>There is no bozo_id to add!</p>";
    header("Location: " . $_SERVER['HTTP_REFERER']);
    exit();
} else {
    if (!isset($_SESSION['authenticated_user_id'])) {
        $_SESSION['error_msg'] = "<p>No authenticated user ID. Setting it now.</p>";
        $_SESSION['authenticated_user_id'] = get_user_id($_SESSION['authenticated_username']);
    }

    $query = "SELECT COUNT(bozo_id) FROM user_bozo WHERE bozo_id = ? AND user_id = ?";
    $stmt = $db->prepare($query);
    $stmt->execute([$uid, $_SESSION['authenticated_user_id']]);

    if ($stmt->fetchColumn() > 0) {
        $_SESSION['error_msg'] = "<p>This person is already a bozo!</p>";
        header("Location: " . $_SERVER['HTTP_REFERER']);
        exit();
    }

    $bozoname = addslashes(get_username($uid));

    if (!isset($_SESSION['authenticated_user_id'])) {
        $_SESSION['error_msg'] = "<p>You need to be logged in to do this. No user_id!</p>";
        header("Location: " . $_SERVER['HTTP_REFERER']);
        exit();
    }

    $query = "INSERT INTO user_bozo (user_id, bozo_id, bozoname) VALUES (?, ?, ?)";
    $stmt = $db->prepare($query);
    $stmt->execute([$_SESSION['authenticated_user_id'], $uid, $bozoname]);

    $_SESSION['success_msg'] = "This bozo was successfully added!";
    header("Location: " . $_SERVER['HTTP_REFERER']);
    exit();
}
?>
