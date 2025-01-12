<?php
// Initialize database connection
require_once("global.php");

// Initialize the HTML output
$html = <<<EOT
<!-- BEGIN PHP Dynamically Required File: roll_call_all.inc -->

<!-- WHAT IS GOING ON IN THE WORLD...  WHO?  -->

<CENTER>
<H1>THE GREAT WALL OF SWINNEY</H1>
</CENTER>
EOT;

// SQL query to fetch the list of users and their article counts
$query = "SELECT user.user_id, user.username, COUNT(articles_info.user_id) AS count 
          FROM user 
          JOIN articles_info ON user.user_id = articles_info.user_id 
          WHERE articles_info.status IN (2) 
          GROUP BY user.user_id 
          ORDER BY username";

$res = $db->query($query);

$html .= "<TABLE ALIGN=CENTER><TR>";

// Initialize index at zero for modulo calculation
$index = 0;

// Loop through the results and generate the HTML output
while ($d = $res->fetchRow(DB_FETCHMODE_OBJECT)) {
    // Increment the index for modulo
    $index++;
    $remainder = $index % 3;
    
    // Sanitize and prepare the username and user_id for output
    $username = strtoupper(htmlspecialchars(stripslashes($d->username), ENT_QUOTES, 'UTF-8'));
    $user_id = intval($d->user_id);
    
    $html .= <<<EOT
<TD>
<a href='info_user.php?uid=$user_id'>$username</a> ($d->count)
</TD>\n
EOT;

    // Add a new row every 3 items
    if ($remainder == 0) {
        $html .= "</TR><TR>\n";  
    }
}

// Close the table and HTML
$html .= "</TR></TABLE>
<!-- END PHP Dynamically Required File: roll_call_all.inc -->
";

// Output the HTML
echo $html;
?>
