## ADDED Requirements

### Requirement: All mysql_* calls are replaced with PEAR DB equivalents
The application SHALL NOT contain any calls to `mysql_query()`, `mysql_fetch_object()`, `mysql_fetch_row()`, `mysql_fetch_array()`, `mysql_num_rows()`, `mysql_result()`, `mysql_affected_rows()`, `mysql_error()`, `mysql_insert_id()`, or `mysql_close()`. All database operations SHALL use the PEAR DB `$db` connection object already initialized in `global.php`.

#### Scenario: No mysql_* functions remain in codebase
- **WHEN** LSP diagnostics are checked across all files in `web/` and `lib/`
- **THEN** zero P1010 (undefined function) errors exist for any `mysql_*` function

#### Scenario: Database queries execute without fatal errors
- **WHEN** any page that performs a database query is loaded (article view, search, rollcall, admin listing, VIP edit)
- **THEN** the page renders without PHP fatal errors

### Requirement: All session_register() calls are replaced with $_SESSION superglobal
The application SHALL NOT contain any calls to `session_register()`. All session variable storage SHALL use `$_SESSION['key'] = $value` syntax.

#### Scenario: No session_register() calls remain
- **WHEN** LSP diagnostics are checked across all files in `web/`
- **THEN** zero P1010 (undefined function) errors exist for `session_register`

#### Scenario: Session variables are preserved
- **WHEN** a user logs in and session variables are set (authenticated_username, authenticated_user_id)
- **THEN** the session values persist across subsequent requests identically to the previous behavior

### Requirement: All ereg_replace() calls are replaced with preg_replace()
The application SHALL NOT contain any calls to `ereg_replace()`, `ereg()`, or `eregi()`. All regex operations SHALL use PCRE functions (`preg_replace()`, `preg_match()`).

#### Scenario: No POSIX regex functions remain
- **WHEN** LSP diagnostics are checked across all files in `web/` and `lib/`
- **THEN** zero P1010 (undefined function) errors exist for `ereg_replace`, `ereg`, or `eregi`

#### Scenario: Regex replacements produce identical output
- **WHEN** `bin()` function converts a decimal to binary and pads with zeros
- **THEN** the output is identical to the previous `ereg_replace(" ", "0", $bin)` behavior

#### Scenario: File regex names produce identical output
- **WHEN** `File::regexNames()` or `show_img()` processes image placeholders in article text
- **THEN** the `%%img1%%` / `%%file1%%` placeholders are replaced with image URLs identically to previous behavior

### Requirement: No debug artifacts remain in production code
The application SHALL NOT contain `var_dump()` or `print_r()` calls in production code paths (commented-out debug lines are acceptable).

#### Scenario: No active var_dump calls
- **WHEN** LSP diagnostics and code review are performed on files known to contain debug artifacts
- **THEN** zero `var_dump()` or `print_r()` calls exist in active (non-commented) code paths

### Requirement: All undefined symbols referenced by the legacy code are defined
The application SHALL define all constants and variables required by its functions. Specifically, the constant `OK` SHALL be defined and the `is_auth()` function SHALL return it on successful authentication checks.

#### Scenario: is_auth() returns a defined value
- **WHEN** `is_auth()` is called for an authenticated user
- **THEN** it returns the constant `OK` which is defined and evaluates to a truthy value

#### Scenario: Multi.php methods have database access
- **WHEN** any method in `Multi.php` that performs a database query is called
- **THEN** the `$db` variable is accessible within the method scope (via `global $db` declaration)
