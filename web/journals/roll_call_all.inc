







<!-- BEGIN PHP Dynamically Required File: roll_call_all.inc -->


<!-- WHAT IS GOING ON IN THE WORLD...  WHO?  -->

<!-- <*austin*> i am a fucking phat php coder and the dude ox at surfmetro can eat my spunk  -->



<?

include "connect.inc";

$res = mysql ("$DB", "SELECT DISTINCT username FROM pending_articles WHERE status='2' OR status='3' ORDER BY username");



  echo "<TABLE><TR>";

  // initialize index at zero for modulo
  $index = 0;


  
while ($row = mysql_fetch_object ($res)) {
  $res2 = mysql ("$DB", "SELECT count(*) FROM pending_articles WHERE username='$row->username'");
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











