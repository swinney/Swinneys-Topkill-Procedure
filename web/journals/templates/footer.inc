<?

$noslogan = array( 1 => 
		   'affectation',
		   'car',
		   'dinner',
		   'doughnuts',
		   'enduring',
		   'estrellas',
		   'exploder',
		   'interrogative',
		   'life',
		   'loves',
		   'not',
		   'old',
		   'oven',
		   'routine',
		   'shit',
		   'smile',
		   'tastes',
		   'why'
		   );

  $num = dice(1, count($noslogan));

?>

<table width="100%">
<tr>
<td>
<img src="<? echo URLBASE; ?>/journals/img/no.gif" alt="" width="58" height="30" border="0">
</td>
</tr>

<tr>
<td align="center">
<a href="<? echo URLBASE; ?>"><img src="<? echo URLBASE; ?>/journals/img/copyright2001.gif" alt="copyright2001.gif" width="43" height="30" border="0"><img src="<? echo URLBASE; ?>/journals/img/no-slogan/<? echo "$noslogan[$num]"; ?>.gif" alt="Copyright 2001, Swinney Loves You." border="0"><img src="<? echo URLBASE; ?>/journals/img/cities.gif" alt="Austin * San Francisco * Melbourne * New York" width="329" height="30" border="0"></a></td>
</tr>

<!-- also, Toronto.  or Montreal.  somewhere in Canada, anyway.  yeah. -->

<tr>
<td align="center">
<img src="<? echo URLBASE; ?>/journals/img/no.gif" alt="" width="1" height="30" border="0">
<?
if (defined("URLBASE")) {
#include_once("URLBASE/journals/insert_stats.inc");
}
?>
</td>
</tr>
</table>
</body>
</html>
<?
$res = $db->disconnect();
?>
