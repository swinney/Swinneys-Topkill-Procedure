<?
# experiments in binary
include "global.inc";

$b0=00000001;
$b1=00000010;
$b2=00000100;
$b3=00001000;
$b4=00010000;
$b5=00100000;
$b6=01000000;
$b7=10000000;

$c[0]=1<<1;     $cb[0]=bin($c[0]);

$c[$i]=$c[$i-1]<<1; $cb[$i]=bin($c[$i]);
$i++;
$c[$i]=$c[$i-1]<<1; $cb[$i]=bin($c[$i]);
$i++;
$c[$i]=$c[$i-1]<<1; $cb[$i]=bin($c[$i]);
$i++;


echo <<<EOT



<H2>static bin table</H2>
<PRE>
$cb[0] is $c[0]
$cb[1] is $c[1]
$cb[2] is $c[2]

00000001 is $b0
00000010 is $b1
00000100 is $b2
00001000 is $b3
00010000 is $b4
00100000 is $b5
01000000 is $b6
10000000 is $b7
</PRE>
EOT;


echo "<H2>automated bin table</H2>";
echo "<PRE>";
for ($i=0; $i<=7; $i++) {
  $m=$i-1;
  echo "c: $c[$i]; cb: $cb[$i];\n";
  $c[$i]=$c[$i]<<1; $cb[$i]=bin($c[$i]);

  print "$cb[$i] is $c[$i]\n";


}
echo "</PRE>";

1


?>