<?php
require_once("User.php");

$user = new Swinsite_User($_SESSION['authenticated_user_id']);
$rv = $user->restore();
if (PEAR::isError($rv)) {
    die(error_page($rv));
}

$bozoSet = $user->bozos();
$bozos = $bozoSet->getAll();
if (PEAR::isError($bozos)) {
    die(error_page($bozos));
}
?>

<table cellpadding="2" cellspacing="0" border="0" width="375">
<tr>
<td>
<p>
<?php
if (isset($error_msg)) {
    unset($_SESSION['error_msg']);
    echo '<span class="header"><b>' . htmlspecialchars($error_msg) . '</b></span>';
} elseif (isset($success_msg)) {
    unset($_SESSION['success_msg']);
    echo '<span class="header"><b>' . htmlspecialchars($success_msg) . '</b></span>';
} else {
    echo '<span class="header"><b>' . htmlspecialchars($title) . '</b></span>';
}
?>
<br>
Is someone a clown? Don't want to see what they have to say? Add them
to your bozolist and their articles and comments will be filtered from
your view of the site.
</p>
</td>
</tr>
</table>

<form method="POST" action="process_bozo.php">
<table cellpadding="2" cellspacing="0" border="0">
<tr>
<td align="right"><p>username:</p></td>
<td align="left">
<input type="text" name="bozo_username" size="20" maxlength="20">
</td>
</tr>
<tr>
<td align="left">&nbsp;</td>
<td align="left">
<input type="submit" name="add" value="add bozo">
</td>
</tr>
</table>

<?php
if (!empty($bozos)) {
    echo '<br>
    <table cellpadding="2" cellspacing="0" border="0" width="375">
    <tr>
    <td><p>If forgiveness is in order, select one or more usernames below and remove them from the list.</p></td>
    </tr>
    </table>
    <br>
    <table cellpadding="2" cellspacing="0" border="0">
    <tr>
    <td align="right" valign="top"><p>username:</p></td>
    <td align="left">
    <select name="bozo_ids[]" size="5" multiple>';

    foreach ($bozos as $bozo) {
        $id = $bozo->id();
        $name = htmlspecialchars($bozo->username());
        echo "<option value=\"$id\"> $name</option>";
    }

    echo '</select></td></tr></table>';
}
?>
