## 1. Constants & Globals Setup

- [x] 1.1 Add `define('OK', true);` to `web/journals/global.php` in the constants block (after line 106)
- [x] 1.2 Remove `var_dump($img_names)` from `web/journals/article.php:59`
- [x] 1.3 Remove `var_dump($error_msg)` from `web/index.php:32`

## 2. Replace ereg_replace() with preg_replace()

- [x] 2.1 Replace `ereg_replace(" ","0",$bin)` with `preg_replace("/ /","0",$bin)` in `web/journals/global.php:297` (`bin()` function)
- [x] 2.2 Replace `ereg_replace($out[0][$i],$replace,$text)` with `preg_replace("/".preg_quote($out[0][$i],"/")."/", $replace, $text)` in `web/journals/global.php:374` (`show_img()` function)
- [x] 2.3 Replace `ereg_replace($out[0][$i],$replace,$text)` with `preg_replace("/".preg_quote($out[0][$i],"/")."/", $replace, $text)` in `lib/Swinsite/File.php:120` (`regexNames()` method)

## 3. Replace session_register() with $_SESSION

- [x] 3.1 Replace `session_register("sess_lang")` → `$_SESSION['sess_lang'] = $lang_cond` in `web/journals/global.php:177`
- [x] 3.2 Replace all `session_register()` calls in `web/journals/process_comment.php` (lines 19, 25, 31, 37, 114) — 4 error_msg + 1 last_lang
- [x] 3.3 Replace all `session_register()` calls in `web/journals/process_login.php` (lines 35, 79) — error_msg
- [x] 3.4 Replace all `session_register()` calls in `web/journals/process_register.php` (lines 42, 82, 85) — error_msg, user_id, authenticated_username
- [x] 3.5 Replace all `session_register()` calls in `web/journals/process_bozo_id.php` (lines 8, 17, 20, 27, 34, 49) — error_msg, authenticated_user_id, success_msg
- [x] 3.6 Replace all `session_register()` calls in `web/journals/process_article.php` (lines 7, 15, 34, 209, 212) — error_msg, last_lang, bin, success_msg
- [x] 3.7 Replace `session_register("last_lang")` in `web/journals/process_thought.php:46` and `web/chat/process_thought.phtml:30`
- [x] 3.8 Replace `session_register("refreshrate")` in `web/chat/index.phtml:7`
- [x] 3.9 Replace `session_register("back_to")` in `web/journals/login.inc:9`
- [x] 3.10 Replace all `session_register()` calls in `web/journals/vip/process_article.phtml` (lines 20, 125, 128) — bin, error_msg, success_msg
- [x] 3.11 Replace `session_register("temp_aid")` in `web/journals/vip/edit_article.phtml:31`
- [x] 3.12 Replace `session_register()` calls in `web/journals/vip/process_bozo.phtml` (lines 47, 87, 105, 109) — bozo_set, error_msg, success_msg
- [x] 3.13 Replace `session_register()` calls in `web/journals/madmin/process_modify_user.phtml` (lines 66, 76) — success_msg, error_msg
- [x] 3.14 Replace `session_register("aindex")` in `web/journals/madmin/submit_image.phtml:8`
- [x] 3.15 Replace `session_register("limit_chars")` in `web/journals/vip/submit_noise.inc:59`
- [x] 3.16 Replace `session_register("error_msg")` in `web/journals/process_category.php:12` — inside comment block, no active call
- [x] 3.17 Replace `session_register("bin")` in `web/journals/process_article.php:34` (covered by 3.6)

## 4. Replace mysql_* in global.php

- [ ] 4.1 Replace `mysql_query/mysql_num_rows/mysql_result` in `get_img()` (lines 336-338) with PEAR DB `$db->query()` and `$db->fetchRow()`
- [ ] 4.2 Replace `ereg_replace` in `show_img()` already handled in 2.2 — verify no remaining mysql_* in show_img
- [ ] 4.3 Replace `mysql_query/mysql_num_rows/mysql_result` in `get_user_id()` (lines 406-408) with PEAR DB `$db->query()` and `$db->fetchOne()`
- [ ] 4.4 Replace `mysql_query/mysql_error/mysql_fetch_row` in `get_rollcall()` (lines 485-488) with PEAR DB
- [ ] 4.5 Replace `mysql_query/mysql_error/mysql_fetch_object` in `get_bozo_set()` (lines 595-598) with PEAR DB

## 5. Replace mysql_* in lib/Swinsite/

- [ ] 5.1 Fix `Multi.php:get_multi_id()` — add `global $db;`, replace `$db->query()` result handling (line 8 already uses $db but without `global` declaration)
- [ ] 5.2 Fix `Multi.php:get_abstract()` — add `global $db;`, replace `mysql_query`/`mysql_result` (lines 27-28)
- [ ] 5.3 Fix `Multi.php:get_multi_fm_id()` — add `global $db;`, fix `$query .=` to `$query =`, replace `mysql_query`/`mysql_fetch_array` (lines 33-37)
- [ ] 5.4 Fix undefined `$description` variable in `File.php:68` (parameter missing from `addInfo` method)

## 6. Replace mysql_* in web/journals/ page scripts

- [ ] 6.1 Replace mysql_* in `search.php` — 11 calls: mysql_query (×5), mysql_num_rows (×2), mysql_fetch_object (×3), mysql_affected_rows (×1)
- [ ] 6.2 Replace mysql_* in `process_comment.php:106,111` — mysql_query (×2)
- [ ] 6.3 Replace mysql_* in `process_register.php` — mysql_query (×3), mysql_num_rows (×1), mysql_error (×2)
- [ ] 6.4 Replace mysql_* in `process_login.php:100` — mysql_query (×1)
- [ ] 6.5 Replace mysql_* in `process_logout.php:4` — mysql_query (×1)
- [ ] 6.6 Replace mysql_* in `process_bozo_id.php:24-25` — mysql_query (×1), mysql_result (×1)
- [ ] 6.7 Replace mysql_* in `process_image.php:43,47` — mysql_query (×1), mysql_error (×1)
- [ ] 6.8 Replace mysql_* in `process_article.php:202,220-221` — mysql_error (×1), mysql_query (×1), mysql_result (×1)
- [ ] 6.9 Replace mysql_* in `process_category.php:21,30` — mysql_query (×2)
- [ ] 6.10 Replace mysql_* in `submit_comment.inc:58-59,83,85` — mysql_query (×2), mysql_fetch_object (×2)
- [ ] 6.11 Replace mysql_* in `submit_category.inc:42,47` — mysql_query (×1), mysql_fetch_object (×1)
- [ ] 6.12 Replace mysql_* in `submit_article.inc:145,150` — mysql_query (×1), mysql_fetch_object (×1)
- [ ] 6.13 Replace mysql_* in `insert_userpages.inc:5,15,28` and `insert_userpages.php:14,27` — mysql_query, mysql_fetch_object, mysql_num_rows
- [ ] 6.14 Replace mysql_* in `insert_alpha.inc:12-16` — mysql_query (×1), mysql_num_rows (×1), mysql_fetch_object (×1)
- [ ] 6.15 Replace mysql_* in `insert_user_comments.inc:27,127-128,130` — mysql_query (×2), mysql_num_rows (×1), mysql_fetch_object (×1)
- [ ] 6.16 Replace mysql_* in `insert_stats.inc:2` — nested mysql_fetch_row(mysql_query(...))
- [ ] 6.17 Replace mysql_* in `bin.inc:20-21,26-27` — mysql_query (×2), mysql_result (×2)
- [ ] 6.18 Replace mysql_* in `roll_call_all.inc:18,25` — mysql_query (×1), mysql_fetch_object (×1)
- [ ] 6.19 Replace mysql_* in `insert_thought.php:27,36` (commented-out lines — verify no active calls)
- [ ] 6.20 Replace mysql_* in `process_thought.php` — verify no active mysql_* calls beyond session_register

## 7. Replace mysql_* in admin/

- [ ] 7.1 Replace mysql_* in `admin/listcontent.php` — mysql_query (×6), mysql_affected_rows (×2), mysql_fetch_object (×2), mysql_fetch_row (×1), mysql_num_rows (×1)
- [ ] 7.2 Replace mysql_* in `admin/edit_comments.php:29,33-39` — mysql_query (×1), mysql_result (×7)
- [ ] 7.3 Replace mysql_* in `admin/admin_comments.php:33,35` — mysql_query (×1), mysql_fetch_object (×1)
- [ ] 7.4 Replace mysql_* in `admin/admin_comments_article.php:19,21` — mysql_query (×1), mysql_fetch_object (×1)
- [ ] 7.5 Replace mysql_* in `admin/edit_article.php:6,17,121,123` — mysql_query (×2), mysql_fetch_object (×1), mysql_fetch_row (×1)
- [ ] 7.6 Replace mysql_* in `admin/submit_article.php:6,17,122,124` — mysql_query (×2), mysql_fetch_object (×1), mysql_fetch_row (×1)
- [ ] 7.7 Replace mysql_* in `admin/articles.php:30-31` — mysql_query (×1), mysql_fetch_object (×1)
- [ ] 7.8 Replace mysql_* in `admin/process_edit_comments.php:5` — mysql_query (×1)
- [ ] 7.9 Replace mysql_* in `admin/cat_call.inc:41-42,50,52` — mysql_query (×2), mysql_result (×1), mysql_fetch_object (×1)

## 8. Replace mysql_* in madmin/

- [ ] 8.1 Replace mysql_* in `madmin/process_articles_text.phtml` — mysql_query (×8), mysql_affected_rows (×2), mysql_insert_id (×2)
- [ ] 8.2 Replace mysql_* in `madmin/users.phtml` — mysql_query (×3), mysql_num_rows (×1), mysql_fetch_object (×4), mysql_error (×2)
- [ ] 8.3 Replace mysql_* in `madmin/articles.phtml` — mysql_query (×1), mysql_num_rows (×1), mysql_fetch_object (×1)
- [ ] 8.4 Replace mysql_* in `madmin/preview_article.phtml:17,19` — mysql_query (×1), mysql_fetch_array (×1)
- [ ] 8.5 Replace mysql_* in `madmin/article_info.phtml:12-13` — mysql_query (×1), mysql_fetch_array (×1)
- [ ] 8.6 Replace mysql_* in `madmin/status.phtml:16-17` — mysql_query (×1), mysql_fetch_row (×1)
- [ ] 8.7 Replace mysql_* in `madmin/submit_image.phtml:15-16,38-39` — mysql_query (×2), mysql_result (×2)
- [ ] 8.8 Replace mysql_* in `madmin/process_status.phtml:9` — mysql_query (×1)
- [ ] 8.9 Replace mysql_* in `madmin/submit_articles_text.inc:29-30` — mysql_query (×1), mysql_fetch_object (×1)
- [ ] 8.10 Replace mysql_* in `madmin/process_modify_user.phtml:62-63` — mysql_query (×1), mysql_error (×1)
- [ ] 8.11 Replace mysql_* in `madmin/process_image.phtml:27,31` — mysql_query (×1), mysql_error (×1)
- [ ] 8.12 Replace mysql_* in `madmin/categorize_article.phtml:29,31` — mysql_query (×1), mysql_fetch_object (×1)

## 9. Replace mysql_* in vip/ and chat/

- [ ] 9.1 Replace mysql_* in `vip/process_article.phtml:72,112,115,118` — mysql_query (×2), mysql_error (×2)
- [ ] 9.2 Replace mysql_* in `vip/edit_article.phtml:19-28` — mysql_query (×1), mysql_result (×8)
- [ ] 9.3 Replace mysql_* in `vip/process_abstract.phtml:8` — mysql_query (×1)
- [ ] 9.4 Replace mysql_* in `vip/submit_message.inc:16-17` — mysql_query (×1), mysql_fetch_object (×1)
- [ ] 9.5 Replace mysql_* in `chat/insert_thought.phtml:27,30` — mysql_query (×1), mysql_fetch_object (×1)

## 10. Replace mysql_* in web/shorts/ and web/index.php

- [ ] 10.1 Replace mysql_* in `shorts/index.phtml:10,12-14` — mysql_query (×1), mysql_result (×3)
- [ ] 10.2 Replace mysql_* in `shorts/process_short.phtml:10` — mysql_query (×1)

## 11. Verification

- [ ] 11.1 Check LSP diagnostics across all modified files — verify zero P1010 (undefined function) errors for `mysql_*`, `session_register`, `ereg_replace`
- [ ] 11.2 Check LSP diagnostics — verify zero P1008 (undefined variable) errors introduced by the changes
- [ ] 11.3 Check LSP diagnostics — verify zero P1011 (undefined constant) errors for `OK`
- [ ] 11.4 Verify no active `var_dump()` calls remain in production code paths
