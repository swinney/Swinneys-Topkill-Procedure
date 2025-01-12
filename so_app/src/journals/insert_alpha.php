<?php
// Ensure session variable for DSN exists
if (!isset($_SESSION['dsn'])) {
    die('Database connection information missing.');
}

// Set database options (optional, can be adjusted based on your needs)
$options = array(
    'persistent' => true, // Using persistent connection for efficiency
);

// Create a database connection using PEAR::DB
$db = DB::connect($_SESSION['dsn'], $options);
if (PEAR::isError($db)) {
    die('Database connection failed: ' . $db->getMessage());
}

// Define alphabet array
$alpha = array(1 => "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z");

// Initialize $i if it's not set
if (!isset($i)) {
    $i = 1;
}

// Main logic when $i is set
if ($i) {
    // Prepare the query using proper escaping to prevent SQL injection
    $letter = $alpha[$i];
    $query = "SELECT article_id, title 
              FROM articles_info 
              WHERE status = 2 
              AND title REGEXP '^([0-9]{1,4}[/-]{0,1}[0-9]{0,4} +){0,1}($letter)+'
              ORDER BY title ASC";
    
    // Execute the query
    $res = $db->query($query);
    if (PEAR::isError($res)) {
        die($res->getMessage());
    }

    // Initialize message and body
    $num_rows = $res->numRows();
    if ($num_rows > 0) {
        $num_mssg = "<p>These titles were brought to you by the letter <b><font size='7'>" . strtoupper($letter) . "</font></b>.</p>";
        $html_body = '';
        
        // Fetch and display rows
        while ($d = $res->fetchRow(DB_FETCHMODE_OBJECT)) {
            $html_body .= "\n<tr><td><a href='./article.php?id={$d->article_id}'>{$d->title}</a></td></tr>";
        }
    } else {
        $num_mssg = "<p>No results returned for the letter <b>{$letter}</b>.</p>";
    }
}

// Navigation through the alphabet
$old = $i;
$i = 1;
$nav = '';

foreach ($alpha as $letter) {
    if ($i != $old) {
        $nav .= "<a href='{$_SERVER['PHP_SELF']}?i=$i'>$letter</a> ";
    } else {
        $nav .= "$letter ";
    }
    $i++;
}

// Output the navigation
echo "<p><font size='5'>$nav</font></p>";

// Output the results and table if any
if (isset($num_mssg)) echo $num_mssg;
if (isset($html_body)) echo "<table>$html_body</table>";

?>
