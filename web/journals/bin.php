<?
# experiments in binary
# funny how little it takes.
include "global.inc";

for ($i=0; $i<=14;$i++) {
$res = 1<<$i;
echo "$res is ". bin($res)."<BR>";
}

?>