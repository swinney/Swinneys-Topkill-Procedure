<?
##################################
# $Id$
# experiments in binary
# funny how little it takes.
echo "<H1>experiments in binary</H1>";
echo "<P><a href=\"". $PHP_SELF ."s\">source file is available</a></P>";

##################################
# bin($dec) function for converting
# decimals to binary.  really just
# to view them in a browser, that is all.
# there is no need to do this otherwise.

function bin($dec){
  $bin = sprintf("%8b", $dec);
  $bin = ereg_replace(" ","0",$bin);
  return $bin;
}


echo "<PRE>";
for ($i=0; $i<=7;$i++) {
$res = 1<<$i;
echo bin($res)." is $res<BR>";
}

$numA=14;
$numB=12;
$res = $numA & $numB;
echo "\n\n$numA & $numB is $res<BR>";
echo "\nA: ". bin($numA);
echo "\nB: ". bin($numB);
echo "</PRE>";
?>