<?
# $Id$
# mo simplified navigation at the top
?>
<p align="center">(
<a href="<? URLBASE ?>" accesskey="h">HOME</A> |
<?
if ($authenticated_username) {
  echo <<<EOT
<a href="process_logout.phtml" accesskey="l">LOG OUT</a> | 
EOT;
} else {
  echo <<<EOT
<a href="login.phtml" accesskey="l">LOG IN</a> | 
EOT;
}
?>
<a href="index.phtml" accesskey="j">JOURNAL</a> |
<a href="comments.phtml" accesskey="c">COMMENTS</a> |
<a href="submit_article.phtml" accesskey="s">SUBMIT</a> |
<a href="faq.phtml" accesskey="f">ANSWERS</A>)</p></b>
