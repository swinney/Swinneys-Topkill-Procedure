<?php
// Initialize session if not started
@session_start();

// Initialize database connection
require_once("global.php");

// No Page Number? Set it to Page 1 then
$page_num = isset($_GET['page_num']) && is_numeric($_GET['page_num']) && $_GET['page_num'] > 0 ? $_GET['page_num'] : 1;

// How many records per page will be displayed...
$per_page = 30;

// Set the page start variable...
$page_start = ($page_num - 1) * $per_page;

$uid = isset($_GET['uid']) ? $_GET['uid'] : null;

// Escape the user ID to prevent SQL injection
$uid = intval($uid);

// Fetch the username securely
$username = $db->getOne("SELECT username FROM user WHERE user_id = ?", [$uid]);

// Query to count the total number of articles/comments
$query = "SELECT COUNT(*) as num_articles FROM comments WHERE status = 0 AND user_id = ?";
$num_articles = $db->getOne($query, [$uid]);

// Query to fetch the comments for the current page
$query = "SELECT comments.comment_id, comments.comment, comments.article_id, comments.username, 
                 articles_info.title, articles_info.username as articlewriter, comments.user_id 
          FROM comments 
          JOIN articles_info ON comments.article_id = articles_info.article_id 
          WHERE comments.user_id = ? 
          AND comments.status = 0 
          ORDER BY comment_id DESC 
          LIMIT ?, ?";
$res = $db->query($query, [$uid, $page_start, $per_page]);

// Calculate the number of pages
$num_of_pages = ceil($num_articles / $per_page);

// Previous and Next page numbers
$page_back = $page_num - 1;
$page_forward = $page_num + 1;

// Begin the HTML output
echo <<<EOT
<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td nowrap>
<span class="subheader"><b>{$username} &raquo;</b></span></td>

<td>&nbsp;&nbsp;&nbsp;</td>

<td align="left">
<span class="subheader"><a href="userpages.php?uid={$uid}">Articles</a> | <b>Comments</b></span></td>
</tr>
<tr><td colspan="2">&nbsp;</td><td align="left"><span class="text">
EOT;

// Pagination links
if ($page_num < $num_of_pages) {
    echo '<a href="' . htmlspecialchars($_SERVER['PHP_SELF']) . '?uid=' . $uid . '&page_num=' . $page_forward . '">&laquo; earlier comments</a>';
}
if ($page_num > 1) {
    echo ' - <a href="' . htmlspecialchars($_SERVER['PHP_SELF']) . '?uid=' . $uid . '&page_num=' . $page_back . '">later comments &raquo;</a>';
}

echo "</span></td></tr></table><br>";

echo <<<EOT
<table cellpadding="0" cellspacing="0" border="0" width="375">
<tr><td><img src="img/no.gif" alt="" width="1" height="4" border="0"></a><br></td></tr>
<tr><td bgcolor="#999999"><img src="img/no.gif" alt="" width="1" height="1" border="0"><br></td></tr>
<tr><td><img src="img/no.gif" alt="" width="1" height="4" border="0"><br></td></tr>
EOT;

// Display fetched comments
while ($d = $res->fetchRow(DB_FETCHMODE_OBJECT)) {
    $article_id = $d->article_id;
    $comment_id = $d->comment_id;
    $comment = stripslashes($d->comment);
    $title = htmlspecialchars($d->title);
    $articlewriter = htmlspecialchars($d->articlewriter);

    echo <<<EOT
<tr>
<td><a name="{$comment_id}"></a>
<a href="info_user.php?uid={$d->user_id}">{$username}</a> on
"<b><a href="article.php?id={$article_id}#{$comment_id}">{$title}</a></b>" 
by <a href='userpages.php?username={$articlewriter}'>{$articlewriter}</a>:<br>
{$comment}</td>
</tr>
<tr><td><img src="img/no.gif" alt="" width="1" height="4" border="0"></a><br></td></tr>
<tr><td bgcolor="#999999"><img src="img/no.gif" alt="" width="1" height="1" border="0"><br></td></tr>
<tr><td><img src="img/no.gif" alt="" width="1" height="4" border="0"><br></td></tr>
EOT;
}

echo <<<EOT
</table>
EOT;

// Pagination footer links
if ($page_num < $num_of_pages || $page_num > 1) {
    echo "<p>";

    if ($page_num < $num_of_pages) {
        echo '<a href="' . htmlspecialchars($_SERVER['PHP_SELF']) . '?uid=' . $uid . '&page_num=' . $page_forward . '">&laquo; earlier comments</a>';
    }
    if ($page_num > 1) {
        echo ' - <a href="' . htmlspecialchars($_SERVER['PHP_SELF']) . '?uid=' . $uid . '&page_num=' . $page_back . '">later comments &raquo;</a>';
    }
}
?>
