<?
# $Id$
# mo simplified navigation at the top
?>
<p align="center">(
<a href="../index.phtml" accesskey="h">SWINNEY.O</A>
<?
if ($authenticated_username) {
  echo <<<EOT
| <a href="process_logout.phtml" accesskey="l">LOG OUT</a> 
EOT;
} else {
  echo <<<EOT
| <a href="login.phtml" accesskey="l">LOG IN</a>   
EOT;
}

$url = array (
   "index.phtml"	=> "JOURNALS",
   "comments.phtml"	=> "COMMENTS"
);

foreach ($url as $path => $ref) {
   echo "| <A HREF=\"$path\">$ref</A> ";  
}
echo " )<BR>";
?>