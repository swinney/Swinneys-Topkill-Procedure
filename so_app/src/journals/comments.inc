<?php
// Include the PEAR DB library
$options = array(
    'debug'       => 2,
    'portability' => DB_PORTABILITY_ALL,
);

// Create a database connection
$db = DB::connect($_SESSION['dsn'], $options);
if (PEAR::isError($db)) {
    die('Database connection failed: ' . $db->getMessage());
}

// What page would you like to return?
$return = $_SERVER['PHP_SELF'];

// No Page Number? Set it to Page 1 then
$page_num = $_GET['page_num'] ?? 1;
$page_num = max(1, (int)$page_num); // Ensuring the page number is at least 1

// How many items per page will be displayed...
$per_page = 15;

// Set the page start variable...
$page_start = ($page_num - 1) * $per_page;

// Prepare the base query to count the number of comments
$query = "
    SELECT COUNT(comment_id) AS num_articles
    FROM comments
    WHERE status = 0
";

// Apply filters based on optional parameters
if (isset($bozo_set) && !empty($bozo_set)) {
    $query .= " AND user_id NOT IN (" . implode(',', array_map('intval', $bozo_set)) . ")";
}

if (isset($limit_chars) && is_numeric($limit_chars)) {
    $query .= " AND chars > ?";
    $params[] = $limit_chars;
}

$lang_str = '';
if (isset($sess_lang) && is_array($sess_lang)) {
    $lang_str = implode(",", array_map([$db, 'quote'], $sess_lang));
    $query .= " AND language IN ($lang_str)";
}

if (isset($insert_since) && is_numeric($insert_since)) {
    $query .= " AND timestamp > ?";
    $params[] = $insert_since;
}

$query .= " ORDER BY comment_id DESC";

$result = $db->query($query, $params ?? []);
if (PEAR::isError($result)) {
    die('Query failed: ' . $result->getMessage());
}

$row = $result->fetchRow(DB_FETCHMODE_ASSOC);

if ($row) {
    $num_of_results = $row['num_articles'];
    $num_of_pages = ceil($num_of_results / $per_page);

    $page_back = $page_num - 1;
    $page_forward = $page_num + 1;

    // Prepare the query to fetch the current page comments
    $query = "
        SELECT username, user_id, to_user_id, comment, comment_id, article_id, language
        FROM comments
        WHERE status = 0
    ";

    if (isset($bozo_set) && !empty($bozo_set)) {
        $query .= " AND user_id NOT IN (" . implode(',', array_map('intval', $bozo_set)) . ")";
    }

    if (isset($limit_chars) && is_numeric($limit_chars)) {
        $query .= " AND chars > ?";
        $params[] = $limit_chars;
    }

    if (isset($sess_lang) && is_array($sess_lang)) {
        $lang_str = implode("','", array_map([$db, 'quote'], $sess_lang));
        $query .= " AND language IN ($lang_str)";
    }

    if (isset($insert_since) && is_numeric($insert_since)) {
        $query .= " AND timestamp > ?";
        $params[] = $insert_since;
    }

    $query .= " ORDER BY comment_id DESC LIMIT ?, ?";
    $params[] = $page_start;
    $params[] = $per_page;

    $result = $db->query($query, $params);
    if (PEAR::isError($result)) {
        die('Query failed: ' . $result->getMessage());
    }

    // Output paginator
    @$url = "article.php?id=@$d->article_id";

    echo <<<EOT
    <table cellpadding="0" cellspacing="0" border="0">
    <tr>
        <td nowrap><span class="subheader"><b>All &raquo;</b></span></td>
        <td>&nbsp;&nbsp;&nbsp;</td>
        <td align="left"><span class="subheader"><a href="index.php">Articles</a> by <a href="alpha.php">Alpha</a> | <b>Comments</b></span></td>
    </tr>
EOT;

    if ($page_num < $num_of_pages || $page_num > 1) {
        echo <<<EOT
        <tr>
            <td colspan="2">&nbsp;</td>
            <td align="left"><span class="text">
EOT;

        if ($page_num < $num_of_pages) {
            echo "<a href=\"$return?page_num=$page_forward\">&laquo; earlier comments</a>";
        }

        if ($page_num < $num_of_pages && $page_num > 1) {
            echo ' - ';
        }

        if ($page_num > 1) {
            echo "<a href=\"$return?page_num=$page_back\">later comments &raquo;</a>";
        }

        echo "</span></td></tr>";
    }

    echo <<<EOT
    </table>
    <br>
    <table cellpadding="0" cellspacing="0" border="0" width="375">
EOT;

    if ($result->numRows() == 0) {
        echo "<p>No comments.</p>";
    } else {
        while ($d = $result->fetchRow(DB_FETCHMODE_OBJECT)) {
            $username = htmlspecialchars($d->username);
            $user_id = $d->user_id;
            $to_user_id = $d->to_user_id;
            $comment = htmlspecialchars(stripslashes($d->comment));
            $article_id = $d->article_id;
            $language = htmlspecialchars($d->language);

            // Build the user link
            if ($user_id != 0) {
                $username = "<a href=\"./info_user.php?uid=$user_id\">$username</a>";
            }

            // Special handling for user 'lulu'
            if ($username == "lulu") {
                $username = "<span style=\"background-color:pink\">$username</span>";
                $comment .= "</span>";
            }

            if (count($sess_lang) > 1) {
                $username .= " [$language]";
            }

            if ($to_user_id != 0) {
                $to_username = get_username($to_user_id);
                $username .= " to <a href='./info_user.php?uid=$to_user_id'>$to_username</a>";
            }

            // Fetch article info
            $article_query = "SELECT username, title, user_id FROM articles_info WHERE article_id = ?";
            $article_result = $db->query($article_query, [$article_id]);
            $article_row = $article_result->fetchRow(DB_FETCHMODE_ASSOC);

            $a_username = htmlspecialchars($article_row['username']);
            $a_title = htmlspecialchars($article_row['title']);

            echo <<<EOT
            <tr>
                <td><a name="$d->comment_id"></a>
                <b>$username</b> on
                "<a href="article.php?id=$article_id#$d->comment_id">$a_title</a>" 
                by <a href='info_user.php?uid={$article_row['user_id']}'>$a_username</a>:<br>
                $comment
                </td>
            </tr>
            <tr>
                <td><img src="img/no.gif" alt="" width="1" height="4" border="0"></a><br></td>
            </tr>
            <tr>
                <td bgcolor="#999999"><img src="img/no.gif" alt="" width="1" height="1" border="0"><br></td>
            </tr>
            <tr>
                <td><img src="img/no.gif" alt="" width="1" height="4" border="0"><br></td>
            </tr>
EOT;
        }
    }

    echo "</table>";

    if ($page_num < $num_of_pages || $page_num > 1) {
        echo "<p>";
        if ($page_num < $num_of_pages) {
            echo "<a href=\"$return?page_num=$page_forward\">&lt;&lt; earlier comments</a>";
        }

        if ($page_num < $num_of_pages && $page_num > 1) {
            echo ' - ';
        }

        if ($page_num > 1) {
            echo "<a href=\"$return?page_num=$page_back\">later comments &gt;&gt;</a>";
        }

        echo "</p>";
    }
}
?>
