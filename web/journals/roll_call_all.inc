<!-- BEGIN PHP Dynamically Required File: roll_call_all.inc -->

<!-- WHAT IS GOING ON IN THE WORLD...  WHO?  -->

<!-- <*austin*> i am a fucking phat php coder and the dude ox at surfmetro can eat my spunk  -->

<?
$res = mysql_query ( "SELECT DISTINCT username FROM articles_info WHERE status='2' OR status='3' ORDER BY username");

  echo "<TABLE><TR>";

  // initialize index at zero for modulo
  $index = 0;

while ($row = mysql_fetch_object ($res)) {
  $res2 = mysql_query ( "SELECT count(*) FROM articles_info WHERE username='$row->username'");
  $count = mysql_fetch_row($res2); 


  // increment the index for modulo
  $index++;
  $remainder = $index % 5;

  echo "<TD><a href='userpages.phtml?username=$row->username'>$row->username($count[0])</a></TD>\n";


  if ($remainder==0) {
  echo "</TR><TR>\n";  
  }

}

echo "</TR></TABLE>";

?>

<!-- END PHP Dynamically Required File: roll_call_all.inc -->











