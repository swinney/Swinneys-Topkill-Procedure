<?php
// Initialize variables from $_GET and sanitize inputs
$uid = isset($_GET['uid']) ? intval($_GET['uid']) : null;
$username = isset($_GET['username']) ? htmlspecialchars($_GET['username'], ENT_QUOTES, 'UTF-8') : null;
$page_num = isset($_GET['page_num']) && is_numeric($_GET['page_num']) && $_GET['page_num'] > 0 ? intval($_GET['page_num']) : 1;

// Default number of articles per page
$per_page = 20;

// Set the page start variable
$page_start = ($page_num - 1) * $per_page;

if ($uid) {
    // Fetch username based on user ID
    $username = $db->getOne("SELECT username FROM user WHERE user_id = ?", [$uid]);
    $url_username = urlencode($username);
} elseif ($username) {
    // Fetch user ID based on username
    $uid = $db->getOne("SELECT user_id FROM user WHERE username = ?", [addslashes($username)]);
}

if (!isset($page_num) || $page_num < 1) {
    // If no page number, set it to 1
    $page_num = 1;
}

// Query to count the total number of articles
if ($uid) {
    $query = "SELECT COUNT(*) as num_articles FROM articles_info WHERE status IN (2, 3) AND user_id = ?";
    $num_of_results = $db->getOne($query, [$uid]);
} elseif ($username) {
    $query = "SELECT COUNT(*) as num_articles FROM articles_info WHERE status IN (2, 3) AND username = ?";
    $num_of_results = $db->getOne($query, [addslashes($username)]);
}

// Query to fetch articles for the current page
if (!$uid) {
    $query = "SELECT article_id, title, blurb, date, username, num_comments FROM articles_info WHERE status IN (2, 3) AND username = ? ORDER BY date DESC LIMIT ?, ?";
    $res = $db->query($query, [addslashes($username), $page_start, $per_page]);
} else {
    $query = "SELECT article_id, title, blurb, date, username, num_comments FROM articles_info WHERE status IN (2, 3) AND user_id = ? ORDER BY article_id DESC LIMIT ?, ?";
    $res = $db->query($query, [$uid, $page_start, $per_page]);
}

// Calculate the total number of pages
$num_of_pages = ($per_page > 0) ? ceil($num_of_results / $per_page) : 0;

// Previous and next page numbers
$page_back = $page_num - 1;
$page_forward = $page_num + 1;

// Begin HTML output
echo <<<EOT
<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td nowrap><span class="subheader"><b>{$username} &raquo;</b></span></td>
<td>&nbsp;&nbsp;&nbsp;</td>
<td align="left"><span class="subheader"><b>Articles</b> | <a href="user_comments.php?uid={$uid}">Comments</a></span></td>
</tr>
<tr><td colspan="2">&nbsp;</td><td align="left"><span class="text">
EOT;

// Pagination links
if ($page_num < $num_of_pages || $page_num > 1) {
    $page_self = htmlspecialchars($_SERVER['PHP_SELF']);
    if ($page_num < $num_of_pages) {
        echo <<<EOT
<a href="{$page_self}?uid={$uid}&page_num={$page_forward}">&laquo; earlier articles</a>
EOT;
    }

    if ($page_num < $num_of_pages && $page_num > 1) {
        echo ' - ';
    }

    if ($page_num > 1) {
        echo "<a href='{$page_self}?uid={$uid}&page_num={$page_back}'>later articles &raquo;</a>";
    }
}
echo "</span></td></tr></table><br>";

echo <<<EOT
<table width="300" border="0" cellspacing="0" cellpadding="0">
<tr><td>
EOT;

// Loop through the results and output each row
while ($individual_row = $res->fetchRow(DB_FETCHMODE_OBJECT)) {
    $article_id = $individual_row->article_id;
    $title = stripslashes($individual_row->title);

    echo <<<EOT
<p><a href="article.php?id={$article_id}">
<b>{$title}</b></a><br>
EOT;

    $blurb = stripslashes($individual_row->blurb);
    if ($blurb) {
        echo $blurb . "<br>\n";
    }

    echo <<<EOT
<span class="small">{$individual_row->date} | {$individual_row->num_comments} comments</span>
</p>
EOT;
}

echo <<<EOT
</td></tr></table>
<p>
EOT;

// Pagination footer links
if ($page_num < $num_of_pages || $page_num > 1) {
    $page_self = htmlspecialchars($_SERVER['PHP_SELF']);
    echo "<p>";
    if ($page_num < $num_of_pages) {
        echo <<<EOT
<a href="{$page_self}?uid={$uid}&page_num={$page_forward}">&laquo; earlier articles</a>
EOT;
    }

    if ($page_num < $num_of_pages && $page_num > 1) {
        echo ' - ';
    }

    if ($page_num > 1) {
        echo <<<EOT
<a href="{$page_self}?uid={$uid}&page_num={$page_back}">later articles &raquo;</a>
EOT;
    }
    echo "</p>";
}
?>
