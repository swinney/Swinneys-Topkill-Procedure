<?
$pending = mysql_fetch_row ( mysql_query ( "SELECT count(status) FROM articles_info where status=1") );
echo <<<EOT
<FONT COLOR="CCCCCC">pending: $pending[0];</FONT>
EOT;
?>
