<?
# $Id$
# mo simplified navigation at the top
?>
<p align="center">(
<a href="../index.php" accesskey="h">SWINNEY.O</A>
<?
if ($_SESSION['authenticated_username']) {
  echo <<<EOT
| <a href="process_logout.php" accesskey="l">LOG OUT</a> 
EOT;
} else {
  echo <<<EOT
| <a href="login.php" accesskey="l">LOG IN</a>   
EOT;
}

$url = array (
   "index.php"	=> "JOURNALS",
   "comments.php"	=> "COMMENTS"
);

foreach ($url as $path => $ref) {
   echo "| <A HREF=\"$path\">$ref</A> ";  
}
echo " )<BR>";
?>