## Context

The legacy Swinney.org codebase (~148 PHP files) uses three categories of functions removed from PHP 7+: `mysql_*` extension (~100+ calls), `session_register()` (~20 calls), and `ereg_replace()` (3 calls). The app ships with a PHP 8.3-FPM container but crashes on every request. PEAR DB is already initialized in `global.php` and provides `$db->query()`, `$db->getRow()`, `$db->getAll()`, and `$db->fetchRow()` methods — so a working database layer already exists alongside the dead `mysql_*` calls.

## Goals / Non-Goals

**Goals:**
- Eliminate every PHP fatal error so the app boots and serves pages on PHP 8.3
- All changes are mechanical replacements — preserve existing behavior exactly
- After this phase, every page (homepage, articles, comments, search, login, admin, VIP) loads without fatals

**Non-Goals:**
- No SQL injection fixes (Phase 2 — PDO migration)
- No XSS fixes (Phase 3 — Twig migration)
- No password hashing upgrades (Phase 3)
- No refactoring, no architectural changes, no new patterns
- No removal of PEAR DB dependency (Phase 2)
- No changes to the new Slim 4 skeleton (`public/`, `src/`, `config/`, `templates/`)

## Decisions

### 1. Bridge to PEAR DB, not PDO

**Decision:** Replace `mysql_*` calls with PEAR DB (`$db->query()`, `$db->fetchRow()`, etc.) rather than jumping directly to PDO.

**Rationale:** PEAR DB is already initialized in `global.php` and used by ~half the codebase. Converting `mysql_*` → PEAR DB is a smaller delta than `mysql_*` → PDO, which would also require setting up a PDO connection, changing fetch modes, and rewriting error handling. PDO migration is Phase 2.

**Alternative considered:** Direct PDO migration — rejected because it conflates two concerns (PHP 8 compat + SQL injection safety) and doubles the blast radius.

### 2. Use `global $db` for class methods

**Decision:** Add `global $db;` declarations to class methods in `Multi.php` and `File.php` that currently call `mysql_*` without any database handle.

**Rationale:** These classes already use `global $db` in some methods (`Multi::is_multi()`, `Multi::get_multi()`). Extending the same pattern is the smallest change. Proper dependency injection comes in Phase 5 (Slim router / controllers).

### 3. Map mysql_* to PEAR DB equivalents

| mysql_* call | PEAR DB replacement |
|---|---|
| `mysql_query($q)` | `$db->query($q)` |
| `mysql_fetch_object($res)` | `$res->fetchRow(DB_FETCHMODE_OBJECT)` |
| `mysql_fetch_row($res)` | `$res->fetchRow()` |
| `mysql_fetch_array($res)` | `$res->fetchRow(DB_FETCHMODE_ASSOC)` |
| `mysql_num_rows($res)` | `$res->numRows()` |
| `mysql_result($res, 0)` | `$res->fetchOne()` |
| `mysql_result($res, 0, N)` | `$row = $res->fetchRow(); $row[N]` |
| `mysql_affected_rows()` | `$db->affectedRows()` |
| `mysql_error()` | `$db->getMessage()` (on error objects) |
| `mysql_insert_id()` | `$db->getOne('SELECT LAST_INSERT_ID()')` |
| `mysql_fetch_row($res)` in while | `while ($row = $res->fetchRow())` |

### 4. session_register() replacement

**Decision:** `session_register("foo")` → `$_SESSION['foo'] = $foo` using the variable's current value at that point in the code. For cases like `session_register("foo", $value)` → `$_SESSION['foo'] = $value`.

### 5. ereg_replace() replacement

**Decision:** `ereg_replace($pattern, $replace, $text)` → `preg_replace("/$pattern/", $replace, $text)` with PCRE delimiters. The 3 existing patterns are simple string matches (space → 0, and regex-escaped file patterns).

### 6. Define missing constant OK

**Decision:** Add `define('OK', true);` to `global.php` alongside the other constants (lines 66-106). The `is_auth()` function returns `OK` on success — callers likely check truthiness.

## Risks / Trade-offs

- **PEAR DB fetch mode differences** → Some `mysql_fetch_object` returns are accessed with `$d->column`. PEAR's `fetchRow(DB_FETCHMODE_OBJECT)` returns the same structure, so this should be transparent.
- **mysql_result() column index** → `mysql_result($res, 0, N)` picks a specific column by index. PEAR has no direct equivalent — must fetch the full row and index into it. Risk: column order must match.
- **mysql_affected_rows() is global** → `mysql_affected_rows()` reads from the last query on the default connection. PEAR's `$db->affectedRows()` does the same but explicitly references the connection object.
- **Missed call sites** → If any `mysql_*` call is missed, the page will fatal. Mitigation: grep sweep after all changes, plus smoke test of every major page.
- **PEAR DB quirks** → PEAR `$db->query()` returns a `DB_result` object on SELECT and `DB_OK` on non-SELECT. Code that checks the return value of INSERT/UPDATE/DELETE queries needs to handle this.
