
<span class="header">

<?
if ($success_msg) {
  echo "<b>$success_msg</b>";
}
else
{
  echo "<b>Settings for $authenticated_username:</b>";
}

?>

</span><br>

<p class="subheader">
<b>&raquo;</b> <a href="submit_change_password.phtml">Change Password</a><br>

<b>&raquo;</b> <a href="submit_bozo.phtml">Edit Bozolist</a></p>
