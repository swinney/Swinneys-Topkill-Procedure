
<span class="header">

<?
if ($success_msg) {
  echo "<b>$success_msg</b>";
}
else
{
  echo "<b>Settings for $_SESSION['authenticated_username']:</b>";
}

?>

</span><br><br>
<table border=0 width="400"><tr><td align="left" valign="left">
<p class="subheader">
Things:<BR>
<b>&raquo;</b> <a href="index_multi.php">Manage Series</a><BR>
<b>&raquo;</b> <a href="edit_article.php">Edit Article</a><BR>
<b>&raquo;</b> <a href="submit_languages.php">Language Filter</a><BR>
<b>&raquo;</b> <a href="submit_lj.php">Your Livejournal RSS</a><BR>
<b>&raquo;</b> <a href="submit_cn.php">Your Citynoise.org Images</a><BR>
<b>&raquo;</b> <a href="submit_friendster.php">Your Friendster Profile</a>

</P>
</td><td>
<p class="subheader">
Stuff:<BR>
<b>&raquo;</b> <a href="submit_location.php">Set Location/Flag</a><br>
<b>&raquo;</b> <a href="submit_change_password.php">Change Password</a><br>
<b>&raquo;</b> <a href="submit_bozo.php">Edit Bozolist</a><BR>
<b>&raquo;</b> <a href="submit_noise.php">Noise Filter</a><BR>
<b>&raquo;</b> <a href="submit_flicker.php">Your Flickr Profile</a>
</P>
</td></tr></table>
