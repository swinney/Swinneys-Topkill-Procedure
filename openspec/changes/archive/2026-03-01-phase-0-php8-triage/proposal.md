## Why

The legacy application cannot run on PHP 8. Every page that touches the database fatals because `mysql_*` functions were removed in PHP 7.0, `session_register()` was removed in PHP 5.4, and `ereg_replace()` was removed in PHP 7.0. The app ships with a PHP 8.3 container but crashes immediately on any request. This must be fixed before any further modernization work can proceed.

## What Changes

- Replace all `mysql_*` function calls (~100+ occurrences across ~30 files) with PEAR `$db->query()` / `$db->getRow()` / `$db->getOne()` / `$db->fetchRow()` — this is a bridge to PDO in a later phase
- Replace all `session_register()` calls (~20 occurrences across 7 files) with `$_SESSION['key'] = $value`
- Replace `ereg_replace()` calls (3 occurrences in `global.php` and `File.php`) with `preg_replace()`
- Remove debug artifacts (`var_dump()` in `article.php:59` and `web/index.php:32`)
- Fix undefined constant `OK` in `global.php:444` (used by `is_auth()`)
- Fix undefined variable `$db` scope issues in `Multi.php` (methods that rely on `global $db` without declaring it)
- Fix `$query .=` without prior initialization in `Multi.php:33`
- Fix undefined variable `$description` in `File.php:68`

## Capabilities

### New Capabilities
- `php8-compat`: Mechanical replacements to eliminate all PHP 7+ fatal errors from the legacy codebase — covers mysql_* removal, session_register removal, ereg_replace removal, and undefined symbol fixes

### Modified Capabilities

(none — no existing spec requirements are changing)

## Impact

- **30+ files** across `web/journals/`, `web/chat/`, `web/shorts/`, `lib/Swinsite/`, `web/journals/admin/`, `web/journals/madmin/`, `web/journals/vip/`
- All changes are mechanical replacements — no business logic changes
- PEAR DB (`$db`) is already initialized in `global.php` and available in most page scripts
- Files using `mysql_*` inside classes (`Multi.php`, `File.php`) need `global $db` declarations or parameter passing
- After this phase, the app should boot and serve pages on PHP 8.3 without fatal errors
