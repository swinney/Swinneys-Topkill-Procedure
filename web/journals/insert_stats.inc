<?
$res = $db->query("SELECT count(status) FROM articles_info where status=1");
$pending = $res->fetchRow();
echo <<<EOT
<FONT COLOR="CCCCCC">pending: $pending[0];</FONT>
EOT;
?>
