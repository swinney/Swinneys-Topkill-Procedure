<?php
// $Id$

$html =<<<EOT
<!-- BEGIN PHP Dynamically Required File: roll_call_all.inc -->

<!-- WHAT IS GOING ON IN THE WORLD...  WHO?  -->

<CENTER>
<H1>THE GREAT WALL OF SWINNEY</H1>
</CENTER>
EOT;

$query = <<<EOT
SELECT user.user_id,user.username,count(articles_info.user_id) as count FROM user,articles_info WHERE user.user_id=articles_info.user_id AND articles_info.status IN (2) GROUP BY user.user_id ORDER BY username
EOT;

$res = mysql_query ($query);

  $html .= "<TABLE ALIGN=CENTER><TR>";

  // initialize index at zero for modulo
  $index = 0;

while ($d = mysql_fetch_object ($res)) {
  // increment the index for modulo
  $index++;
  $remainder = $index % 3;
  $username=stripslashes(strtoupper($d->username));
  $user_id = stripslashes($d->user_id);
  $html .=<<<EOT
<TD>
<a href='info_user.php?uid=$user_id'>$username</a>
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













