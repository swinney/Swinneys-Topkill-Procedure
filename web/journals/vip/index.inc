
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

</span><br><br>
<table border=0 width="400"><tr><td align="left" valign="left">
<p class="subheader">
Things:<BR>
<b>&raquo;</b> <a href="index_multi.phtml">Manage Series</a><BR>
<b>&raquo;</b> <a href="edit_article.phtml">Edit Article</a><BR>
<b>&raquo;</b> <a href="submit_languages.phtml">Language Filter</a><BR>
<b>&raquo;</b> <a href="submit_lj.phtml">Your Livejournal RSS</a><BR>
<b>&raquo;</b> <a href="submit_cn.phtml">Your Citynoise.org Images</a><BR>
<b>&raquo;</b> <a href="submit_friendster.phtml">Your Friendster Profile</a>

</P>
</td><td>
<p class="subheader">
Stuff:<BR>
<b>&raquo;</b> <a href="submit_location.phtml">Set Location/Flag</a><br>
<b>&raquo;</b> <a href="submit_change_password.phtml">Change Password</a><br>
<b>&raquo;</b> <a href="submit_bozo.phtml">Edit Bozolist</a><BR>
<b>&raquo;</b> <a href="submit_noise.phtml">Noise Filter</a><BR>
<b>&raquo;</b> <a href="submit_flicker.phtml">Your Flickr Profile</a>
</P>
</td></tr></table>
