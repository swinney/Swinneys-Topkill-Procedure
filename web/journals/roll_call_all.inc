<?php
// $Id$

$html =<<<EOT
<!-- BEGIN PHP Dynamically Required File: roll_call_all.inc -->

<!-- WHAT IS GOING ON IN THE WORLD...  WHO?  -->

<!-- <*austin*> i am a fucking phat php coder and the dude ox at surfmetro can eat my spunk  -->
<CENTER>
<H1>THE GREAT WALL OF SWINNEY</H1>
</CENTER>
EOT;

$query = <<<EOT
  SELECT DISTINCT(username) as username,
         COUNT(username) count 
    FROM articles_info 
   WHERE status IN (2,3) 
     AND username<>"" 
     AND username=username 
GROUP BY username 
ORDER BY username
EOT;

$res = mysql_query ($query);

  $html .= "<TABLE ALIGN=CENTER><TR>";

  // initialize index at zero for modulo
  $index = 0;

while ($d = mysql_fetch_object ($res)) {
  $url_username=urlencode($d->username);
  // increment the index for modulo
  $index++;
  $remainder = $index % 3;
  $username=strtoupper($d->username);
  $html .=<<<EOT
<TD>
<a href='userpages.phtml?username=$url_username'>$username</a>
    ($d->count)
</TD>\n
EOT;


  if ($remainder==0) {
  $html .= "</TR><TR>\n";  
  }

}

$html .= "</TR></TABLE>
<!-- END PHP Dynamically Required File: roll_call_all.inc -->
";


echo $html;
?>













