# Swinney.org Migration North Star

> **Status:** Living document — project source-of-truth for modernization
> **Last audit:** 2026-03-01
> **Audited with:** PHP LSP (Intelephense) + static analysis of 148 application files

---

## 1. Audit: Gravity Centers

These are the irreplaceable business-logic modules that define what Swinney.org *is*. Everything else is plumbing.

### 1.1 Article Publishing Pipeline

| Component | Location | Role |
|-----------|----------|------|
| `Articles` class | `lib/Swinsite/Articles.php` | ORM — `getArticle()`, `getTitles()`, `getUserTitles()`, `otherArticleId()`, `AddHit()` |
| Article view | `web/journals/article.php` | Entry point — parses `$_GET['id']`, joins articles_info + articles_text + articles_files |
| Article submission | `web/journals/process_article.php` | Form handler — validation, INSERT, email notification |
| Article admin | `web/journals/admin/listcontent.php` | CRUD — status changes, text edits, front-page management |
| Master admin | `web/journals/madmin/` (24 files) | Full editorial dashboard — `.phtml` pages with their own template system |

**Core tables:** `articles_info` (PK `article_id`, metadata), `articles_text` (content body), `articles_files` (attachments), `articles_front` (featured), `articles_comments` (denormalized count)

### 1.2 User & Auth System

| Component | Location | Role |
|-----------|----------|------|
| `User` class | `lib/Swinsite/User.php` | ORM extending `Swinsite_Persistent_Object` — properties: username, email, password, ip_addr, confidence |
| `UserPeer` | `lib/Swinsite/DBPeer/UserPeer.php` | DB peer — `get_select_sql()`, `get_insert_sql()`, `get_update_sql()`, `get_delete_sql()` |
| Auth gate | `web/journals/global.php:442` | `is_auth($thisurl)` — checks `$_SESSION['authenticated_username']`, redirects to login |
| Login flow | `web/journals/process_login.php` | Password check via `crypt()`, sets session + cookies |
| Registration | `web/journals/process_register.php` | Creates user with `crypt()` password, reCAPTCHA integration |
| VIP dashboard | `web/journals/vip/` (26 files) | Authenticated user features — password change, messaging, article management |

**Core tables:** `user` (PK `user_id`), `user_perm`/`perm_set` (permissions), `user_settings`, `user_total`

### 1.3 Comment System

| Component | Location | Role |
|-----------|----------|------|
| Comment rendering | `web/journals/global.php:520` | `get_comments($id, $db)` — builds `HTML_Table` with bozo filtering |
| Comment posting | `web/journals/process_comment.php` | Validates, inserts, updates `num_comments` counter |
| Comment moderation | `web/journals/admin/edit_comments.php` | Status management per comment |

**Core table:** `comments` (PK `comment_id`, FK `article_id`)

### 1.4 Bozo (Ignore) System

| Component | Location | Role |
|-----------|----------|------|
| `Bozos` class | `lib/Swinsite/Bozos.php` | Set-based ORM — wraps `BozosPeer` |
| SQL filter builder | `web/journals/global.php:586` | `get_bozo_set()` — returns `"(id1,id2,...)"` SQL fragment |
| Bozo management | `web/journals/process_bozo_id.php` | Add/remove users from ignore list |

**Pattern:** Bozo set is injected into `WHERE user_id NOT IN $bozo_set` across article listings, comments, and thoughts. This is a cross-cutting concern touching nearly every query.

### 1.5 Multi-Article Series

| Component | Location | Role |
|-----------|----------|------|
| `Multi` class | `lib/Swinsite/Multi.php` | `is_multi()`, `get_multi()`, `get_nav()`, `get_abstract()` |
| Series display | `web/journals/templates/template.inc:14-30` | Conditionally renders series navigation in sidebar |

**Core tables:** `multi_info` (PK `multi_id`), `multi_articles` (junction)

### 1.6 Search

| Component | Location | Role |
|-----------|----------|------|
| Search engine | `web/journals/search.php` (320 lines) | Full-text across articles + comments + users, tracks search terms in `search_words` |

Entirely self-contained in one file. No reusable search service exists.

### 1.7 Chat / Thoughts

| Component | Location | Role |
|-----------|----------|------|
| Thought feed | `web/journals/insert_thought.php` | Renders 5 most recent thoughts with bozo/language filtering, inline image detection |
| Chat UI | `web/chat/` (4 `.phtml` files) | Submit + display interface |

**Core table:** `thoughts`

### 1.8 Initialization Hub

`web/journals/global.php` (~625 lines) is the single point of initialization for every request. It provides:

- 12 configuration constants (lines 66-106)
- PEAR DB connection setup (lines 136-158)
- Session bootstrap (lines 24-27)
- 10 utility functions: `pretty_status`, `use_lib`, `error_page`, `dice`, `bin`, `get_cat_names`, `get_img`, `show_img`, `get_username`, `get_user_id`
- 3 domain functions: `is_auth`, `get_rollcall`, `get_comments`, `get_cat_none`, `get_bozo_set`

### 1.9 Persistent Object Framework

A hand-rolled ORM in `lib/Swinsite/Persistent/`:

```
Swinsite_Persistent_Object    ← base class (id, isNew, isDirty, isDeleted, save/restore/remove)
  └── Swinsite_User           ← concrete model

Swinsite_Persistent_DBPeer    ← abstract CRUD (select/insert/update/delete)
  └── Swinsite_DBPeer_UserPeer ← SQL generation for User

Swinsite_Persistent_Set       ← base collection
  └── Swinsite_Bozos          ← concrete set

Swinsite_Persistent_DBSetPeer ← collection CRUD
  └── Swinsite_DBPeer_BozosPeer ← SQL generation for Bozos
```

Only `User` and `Bozos` use this framework. `Articles`, `Multi`, `File`, and `Search` bypass it with direct SQL.

---

## 2. Audit: Technical Debt

### 2.1 Fatal PHP 8 Incompatibilities (LSP Diagnostics)

These functions are **removed** from PHP and will cause fatal errors:

| Function | Occurrences | Files | Removed In |
|----------|------------|-------|------------|
| `mysql_query()` | 60+ | 20 files | PHP 7.0 |
| `mysql_fetch_object/row/array()` | 40+ | 18 files | PHP 7.0 |
| `mysql_num_rows()` | 15+ | 10 files | PHP 7.0 |
| `mysql_result()` | 12+ | 6 files | PHP 7.0 |
| `session_register()` | 20 | 7 files | PHP 5.4 |
| `ereg_replace()` | 3 | `global.php`, `File.php` | PHP 7.0 |

**Impact:** The application cannot actually run on the PHP 8.2 container it ships with. Every page using `mysql_*` will fatal. The PEAR DB layer (`$db->query()`) works, but ~half the codebase bypasses it.

### 2.2 SQL Injection Vectors

No prepared statements exist anywhere in application code. All queries use string interpolation:

```php
// Articles.php:36 — $id comes from $_GET['id'] (article.php:5)
WHERE articles_info.article_id=$id

// search.php:35 — $find comes from user search input
WHERE title LIKE '%$find%'

// UserPeer.php:37 — builds WHERE with raw property values
"username='$obj->username'"

// process_comment.php:89-104 — addslashes() is NOT safe escaping
$username = addslashes("$username");
```

**Vulnerable entry points:** `article.php`, `search.php`, `process_comment.php`, `process_login.php`, `process_register.php`, `admin/edit_comments.php`, `admin/listcontent.php`, all `Multi.php` methods, all `File.php` methods.

### 2.3 Cross-Site Scripting (XSS)

Pattern: `stripslashes()` is used as output "sanitization" — it does nothing for XSS:

```php
$a_title = stripslashes($row['title']);  // article.php:27
// Then echoed directly in HTML templates with no htmlspecialchars()
```

`htmlspecialchars()` appears in only 1 place (login.php:8). The other 55 occurrences of `stripslashes` provide zero protection.

### 2.4 Global State & Coupling

```php
// Articles.php — uses global $db from global.php
global $db;
global $id;

// DBPeer.php — uses global $SWINSITE registry
global $SWINSITE;

// Template includes expect dozens of variables to be in scope:
// $title, $into_template, $rollcall, $bozo_set, $db, etc.
```

There is no dependency injection, no service container, and no clear contract between files.

### 2.5 Password Storage

```php
// process_register.php:65
$encrypted_password = crypt($password);  // DES or MD5 depending on system

// process_login.php:62
if (crypt($password, $user->password) == $user->password)  // loose comparison
```

Uses `crypt()` with no explicit algorithm. Should be `password_hash()` / `password_verify()` with `PASSWORD_BCRYPT` or `PASSWORD_ARGON2ID`.

### 2.6 No Autoloading

139 `include`/`require` statements across 44 files. Classes use PEAR naming (`Swinsite_User`) instead of PSR-4 namespaces. The `use_lib()` function in global.php manipulates `include_path` at runtime.

### 2.7 Mixed Concerns

Business logic, SQL, HTML generation, and session management are interleaved in single files. Example: `get_comments()` in global.php builds SQL, executes it, instantiates `HTML_Table`, formats output, and returns an HTML string — all in one 52-line function.

### 2.8 Database Schema Issues

- All tables use `MyISAM` (no transactions, no foreign keys, no referential integrity)
- No indexes on foreign keys (`articles_text.article_id`, `comments.article_id`, `multi_articles.article_id`)
- Category system uses bitwise `int(32)` — hard limit of 32 categories
- `ip_addr` stored as `TEXT` (should be `VARCHAR(45)` for IPv6)
- Denormalized `articles_comments` table duplicates `num_comments` from `articles_info`
- Schema frozen since 2011 SQL dump — no migration system

### 2.9 Hardcoded Credentials

```php
// local_conf.php — committed to git
define("DB_USER", "root");
define("DB_PASSWD", "bananas");
```

The `.env` file exists with the same credentials but `local_conf.php` doesn't read from it.

### 2.10 Dead Code & Debug Artifacts

- `article.php:59` — `var_dump($img_names)` left in production code
- `web/journals/article2.php` — duplicate of article.php
- `web/hacked.html` — "Hacked by the Olsen Twins" easter egg
- Multiple `// commented-out` blocks of old mysql_* code alongside PEAR DB code

---

## 3. Target Stack

**Guiding principle:** Smallest leap that delivers real safety. This is a ~94-file PHP app with a single developer — not a candidate for a framework migration to Laravel/Symfony. Stay close to the metal.

| Layer | Current | Target | Why |
|-------|---------|--------|-----|
| **Runtime** | PHP 8.2-FPM | **PHP 8.3+** with `declare(strict_types=1)` | Current LTS, strict types catch bugs at runtime |
| **Routing** | Filesystem (Nginx try_files) | **Slim 4 micro-framework** | Adds PSR-7 request/response, middleware pipeline, DI container — without imposing MVC scaffolding |
| **Database** | PEAR DB + raw `mysql_*` | **PDO with prepared statements** | Native PHP, no dependencies, parameterized queries eliminate SQLi |
| **ORM** | Hand-rolled `Persistent/` | **Keep and modernize** → namespaced, PDO-backed | The peer pattern works; it just needs safe SQL and autoloading |
| **Templates** | `.inc` includes with global vars | **Twig 3** | Auto-escaping (kills XSS by default), template inheritance replaces include chains, clear variable contracts |
| **Auth** | `crypt()` + session globals | **`password_hash()`/`password_verify()`** + session middleware | Modern hashing, HTTP-only cookies, CSRF tokens |
| **Autoloading** | `include_path` + `use_lib()` | **Composer PSR-4** | Standard, cacheable, eliminates manual includes |
| **Config** | `local_conf.php` defines | **`vlucas/phpdotenv`** reading `.env` | Credentials out of code, 12-factor compliant |
| **Container** | Docker Compose (Nginx + PHP-FPM + MySQL) | **Keep** — update `phpfpm.Dockerfile` | Infrastructure is fine; just update PHP version and extensions |
| **Schema** | Raw SQL dump | **Phinx migrations** | Versioned, reversible, trackable schema changes |
| **Testing** | None | **PHPUnit** + basic smoke tests | Start with integration tests on critical paths (login, article view, comment post) |

### What We Are NOT Doing

- **No SPA/frontend framework.** The table-based HTML is the aesthetic. Modernize the backend; leave the 90s look.
- **No full-framework migration.** Laravel/Symfony would require rewriting every file. Slim 4 wraps the existing structure.
- **No API-first rewrite.** Server-rendered HTML is the product. An API can come later if needed.
- **No database migration (MySQL → Postgres).** MySQL is fine. Just fix the schema.

---

## 4. The Plan: Incremental Migration Phases

### Ground Rule
The site must remain functional after every commit. No "big bang" rewrites. Each phase delivers a working application.

---

### Phase 0: Triage — Make It Actually Run on PHP 8
**Goal:** Eliminate every fatal error so the app boots.
**Risk:** Low — these are mechanical replacements.

| Task | Scope | Detail |
|------|-------|--------|
| 0.1 Replace `mysql_*` calls | 20 files, ~60 calls | Replace with PEAR `$db->query()` / `$db->getRow()` / `$db->getOne()` since PEAR DB is already initialized in global.php. This is a bridge — PDO comes in Phase 2. |
| 0.2 Replace `session_register()` | 7 files, 20 calls | Change `session_register("foo")` → `$_SESSION['foo'] = $foo` |
| 0.3 Replace `ereg_replace()` | `global.php`, `File.php` | Change to `preg_replace()` with PCRE delimiters |
| 0.4 Fix LSP diagnostics | 6 files, 15 errors | Undefined variables (`$db` scope in Multi.php), undefined constants (`OK`, `CONF`, `SITE_IMGURL`), property access on Bozos/User |
| 0.5 Remove debug artifacts | `article.php:59` | Delete `var_dump()`, set `ERROR_REP = 0` permanently |
| 0.6 Smoke test | Manual | Boot containers, load homepage, view article, post comment, login, search |

**Deliverable:** App runs on PHP 8.2 without fatals. All existing behavior preserved.

---

### Phase 1: Foundation — Composer, Autoloading, Config
**Goal:** Modern PHP project structure. No behavior changes.

| Task | Scope | Detail |
|------|-------|--------|
| 1.1 Add `composer.json` at project root | New file | Require: `slim/slim`, `slim/psr7`, `php-di/php-di`, `vlucas/phpdotenv`, `twig/twig`. PSR-4 autoload: `Swinsite\\` → `lib/Swinsite/` |
| 1.2 Namespace the Swinsite library | `lib/Swinsite/` (10 files) | `Swinsite_User` → `Swinsite\User`, `Swinsite_Persistent_Object` → `Swinsite\Persistent\BaseObject`, etc. Keep old class names as aliases during transition. |
| 1.3 Move config to `.env` | `local_conf.php` | Read DB credentials and URLBASE from environment. Keep `local_conf.php` as a thin wrapper that calls `$_ENV`. |
| 1.4 Add `bootstrap.php` | New file | Composer autoload, dotenv loading, error handler setup. Included by global.php. |
| 1.5 Remove `use_lib()` and `include_path` manipulation | `global.php` | Composer autoloading replaces this entirely. |

**Deliverable:** `composer install` works. Classes autoload. Credentials are in `.env`.

---

### Phase 2: Database Safety — PDO & Prepared Statements
**Goal:** Eliminate all SQL injection vectors.

| Task | Scope | Detail |
|------|-------|--------|
| 2.1 Create `Database` service class | New file | Wraps PDO connection. Singleton via DI container. Provides `query($sql, $params)`, `getRow()`, `getOne()`, `getAll()`. |
| 2.2 Migrate `global.php` functions to PDO | 5 functions | `get_cat_names()`, `get_img()`, `get_username()`, `get_user_id()`, `get_rollcall()`, `get_comments()`, `get_bozo_set()` |
| 2.3 Migrate `Articles.php` to PDO | 5 methods | All queries use `$db->query($sql, [$id])` with `?` placeholders |
| 2.4 Migrate `UserPeer.php` to PDO | 4 methods | Replace `addslashes()` interpolation with prepared statements |
| 2.5 Migrate `Multi.php` to PDO | 6 methods | Replace all `mysql_*` remnants |
| 2.6 Migrate `File.php` to PDO | 5 methods | Parameterize all file queries |
| 2.7 Migrate page scripts to PDO | `search.php`, `process_*.php`, `admin/*.php` | Every raw SQL call gets parameterized |
| 2.8 Remove PEAR DB dependency | `global.php`, Dockerfile | Delete `$db = DB::connect()`, remove PEAR DB from container |
| 2.9 Convert tables to InnoDB | Migration script | `ALTER TABLE x ENGINE=InnoDB` for all tables |
| 2.10 Add foreign key indexes | Migration script | Index `articles_text.article_id`, `comments.article_id`, `multi_articles.article_id`, etc. |

**Deliverable:** Zero SQL injection vectors. PEAR DB removed. All queries parameterized.

---

### Phase 3: Security Hardening
**Goal:** Fix auth, XSS, CSRF, and session management.

| Task | Scope | Detail |
|------|-------|--------|
| 3.1 Upgrade password hashing | `process_register.php`, `process_login.php`, `User.php` | `password_hash(PASSWORD_ARGON2ID)` for new passwords, `password_verify()` for login. Add migration: on successful login with old `crypt()` hash, re-hash with Argon2 and update DB. |
| 3.2 Secure session configuration | `global.php` / bootstrap | `session_set_cookie_params(['httponly' => true, 'samesite' => 'Lax', 'secure' => true])`. Reasonable expiry (30 days, not 317 years). |
| 3.3 Add CSRF tokens | All forms | Generate token in session, embed in forms as hidden field, validate on POST handlers. Slim middleware can do this globally. |
| 3.4 Output escaping | All templates | Until Twig migration (Phase 4): wrap all user-sourced output in `htmlspecialchars($var, ENT_QUOTES, 'UTF-8')`. Create `e()` helper function. |
| 3.5 Input validation | `process_*.php` files | Validate types, lengths, and formats before any DB interaction. Reject bad input early. |
| 3.6 Remove hardcoded credentials | `local_conf.php` | Already addressed in Phase 1.3 — verify no residual secrets. |
| 3.7 Add security headers | Nginx config or PHP middleware | `X-Content-Type-Options: nosniff`, `X-Frame-Options: DENY`, `Referrer-Policy: strict-origin-when-cross-origin` |

**Deliverable:** Modern auth, no XSS, CSRF protection on all forms, secure sessions.

---

### Phase 4: Separation of Concerns — Twig Templates
**Goal:** Extract HTML from PHP. Clear variable contracts.

| Task | Scope | Detail |
|------|-------|--------|
| 4.1 Set up Twig environment | `bootstrap.php` | Template directory: `web/journals/templates/twig/`. Auto-escaping enabled. |
| 4.2 Convert master layout | `template.inc` → `layout.twig` | Twig `{% block %}` inheritance replaces include chain (`top.inc`, `footer.inc`, `rollcall.inc`, etc.) |
| 4.3 Convert page templates one at a time | Priority order: `index`, `article`, `comments`, `login`, `search` | Each page script becomes a thin controller: fetch data, pass to `$twig->render('page.twig', $data)`. |
| 4.4 Convert admin templates | `admin/` → Twig | Same pattern. Admin gets its own `admin_layout.twig`. |
| 4.5 Convert VIP templates | `vip/` → Twig | User dashboard templates. |
| 4.6 Convert madmin templates | `madmin/` → Twig | Master admin `.phtml` files converted. |
| 4.7 Delete old `.inc` files | Cleanup | Remove all legacy template includes once Twig equivalents are verified. |

**Deliverable:** All HTML in Twig templates. Auto-escaping eliminates XSS class entirely. PHP files contain only logic.

---

### Phase 5: Slim Router & Middleware
**Goal:** Proper HTTP routing, middleware pipeline, DI container.

| Task | Scope | Detail |
|------|-------|--------|
| 5.1 Create Slim app entry point | `web/index.php` (rewrite) | Single front controller. Nginx `try_files` → `index.php`. |
| 5.2 Define routes | Route file | `GET /` → HomeController, `GET /article/{id}` → ArticleController, `POST /comment` → CommentController, etc. |
| 5.3 Extract controllers from page scripts | `article.php` → `ArticleController::show()`, etc. | Each `process_*.php` becomes a controller method. Business logic extracted. |
| 5.4 Auth middleware | New class | Replaces `is_auth()` — applies to route groups (`/admin/*`, `/vip/*`, `/submit/*`). |
| 5.5 CSRF middleware | Slim middleware | Global POST protection via middleware instead of manual token checks. |
| 5.6 Error handling middleware | New class | Replaces `die()` and `error_page()` with proper HTTP error responses. |
| 5.7 DI container | PHP-DI config | Wire Database, Twig, Session services. Controllers receive dependencies via constructor injection. |
| 5.8 Remove `global.php` | Graduation | Its responsibilities are now split across: bootstrap (autoloading), DI container (services), middleware (auth, sessions), and controllers (business logic). |

**Deliverable:** Clean MVC architecture. No global state. Testable controllers.

---

### Phase 6: Schema Migrations & Data Integrity
**Goal:** Versioned schema, proper constraints, modern storage.

| Task | Scope | Detail |
|------|-------|--------|
| 6.1 Set up Phinx | `phinx.yml` + `db/migrations/` | Migration tool connected to MySQL container. |
| 6.2 Baseline migration | First migration | Captures current schema as-is (from `mkdb.sql`). |
| 6.3 Add foreign keys | Migration | `comments.article_id → articles_info.article_id`, `articles_text.article_id → articles_info.article_id`, etc. |
| 6.4 Fix column types | Migration | `ip_addr TEXT → VARCHAR(45)`, `timestamp(12) → TIMESTAMP`, fix enum on `articles_files.ext` |
| 6.5 Remove denormalized tables | Migration | Drop `articles_comments` (use `COUNT()` or maintain `num_comments` via triggers). |
| 6.6 Modernize category system | Migration | Replace bitwise `category int(32)` with junction table `article_categories(article_id, category_id)`. |
| 6.7 Add password hash column | Migration | `ALTER TABLE user ADD password_hash VARCHAR(255)` — coexists with old `password` column during transition. |

**Deliverable:** Schema managed by migrations. Referential integrity enforced. Ready for future changes.

---

### Phase 7: Testing & CI
**Goal:** Confidence for future changes.

| Task | Scope | Detail |
|------|-------|--------|
| 7.1 Add PHPUnit | `composer.json`, `phpunit.xml` | Test framework setup. |
| 7.2 Smoke tests | `tests/Smoke/` | HTTP tests: homepage loads (200), article page loads, login form renders, search returns results. |
| 7.3 Unit tests for services | `tests/Unit/` | Database service, Article repository, User auth service. |
| 7.4 Integration tests | `tests/Integration/` | Full request cycle: submit comment, register user, post article. |
| 7.5 GitHub Actions CI | `.github/workflows/ci.yml` | Run tests on push. `docker-compose up` → PHPUnit → report. |

**Deliverable:** Test suite covering critical paths. CI prevents regressions.

---

## 5. Migration Dependency Map

```
Phase 0: Triage (PHP 8 compat)
   │
   ▼
Phase 1: Foundation (Composer, namespaces, .env)
   │
   ├──────────────────┐
   ▼                  ▼
Phase 2: DB Safety   Phase 3: Security
(PDO, prepared)      (passwords, CSRF, XSS)
   │                  │
   └────────┬─────────┘
            ▼
Phase 4: Twig Templates
            │
            ▼
Phase 5: Slim Router & Middleware
            │
            ▼
Phase 6: Schema Migrations
            │
            ▼
Phase 7: Testing & CI
```

Phases 2 and 3 can run in parallel after Phase 1. Everything else is sequential.

---

## 6. File Impact Heatmap

Files ranked by how many phases touch them — prioritize understanding these:

| File | Phases | Why |
|------|--------|-----|
| `web/journals/global.php` | 0, 1, 2, 3, 5 | Initialization hub — progressively decomposed |
| `lib/Swinsite/Articles.php` | 0, 1, 2 | Core ORM — namespaced, then PDO'd |
| `web/journals/search.php` | 0, 2, 3, 4, 5 | Most vulnerable file — complete rewrite across phases |
| `web/journals/process_login.php` | 0, 2, 3, 5 | Auth flow — hashing + session + controller extraction |
| `web/journals/process_comment.php` | 0, 2, 3, 5 | Comment posting — SQLi + XSS + controller |
| `web/journals/process_register.php` | 0, 2, 3, 5 | Registration — same treatment as login |
| `lib/Swinsite/DBPeer/UserPeer.php` | 1, 2 | Most vulnerable ORM peer |
| `lib/Swinsite/Multi.php` | 0, 1, 2 | Uses mysql_* directly — must be fully migrated |
| `web/journals/admin/listcontent.php` | 0, 2, 4, 5 | Largest admin file — heavy SQL |
| `web/journals/templates/template.inc` | 4 | Master layout → Twig conversion |

---

## 7. Success Criteria

| Phase | Done When |
|-------|-----------|
| 0 | `docker-compose up` → browse homepage, articles, comments, login — zero PHP fatals/warnings |
| 1 | `composer install` works, classes autoload with `use Swinsite\User`, `.env` holds all secrets |
| 2 | `grep -r "mysql_query\|addslashes\|PEAR" web/ lib/` returns zero matches (excluding vendor/) |
| 3 | OWASP ZAP basic scan reports no High/Medium findings on login, search, and comment flows |
| 4 | Zero `.inc` template files remain. All HTML lives in `.twig` files. |
| 5 | `global.php` deleted. All routes defined in route config. `grep -r "global \$" lib/ web/` returns zero. |
| 6 | `phinx migrate` reproduces schema from scratch. All tables InnoDB with foreign keys. |
| 7 | `phpunit` passes. CI green on GitHub. |

---

## Appendix A: LSP Diagnostic Summary (Intelephense)

Captured during audit — these are the errors the PHP language server reports:

**global.php:**
- `session_register` — undefined function (P1010)
- `ereg_replace` — undefined function (P1010)
- `mysql_query`, `mysql_num_rows`, `mysql_result` — undefined functions (P1010)
- `OK` — undefined constant (P1011)

**Multi.php:**
- `$db` — undefined variable (P1008) — relies on `global $db` from caller scope
- `mysql_query`, `mysql_result`, `mysql_fetch_array` — undefined functions (P1010)

**User.php:**
- `$bozos` — undefined property (P1014) — dynamic property on Persistent_Object

**Bozos.php:**
- `$peer` — undefined property (P1014) — dynamic property

**File.php:**
- `CONF`, `SITE_IMGURL` — undefined constants (P1011)
- `$description`, `$error_msg` — undefined variables (P1008)
- `ereg_replace` — undefined function (P1010)

**DBSetPeer.php:**
- `$row` — undefined variable (P1008) — bug: should be `$rows`

**UserPeer.php:**
- Type mismatch in `get_select_sql()` return (P1006)

**article.php:**
- `Articles` — undefined type (P1009) — no autoloading

---

## Appendix B: Inventory Counts

| Category | Count |
|----------|-------|
| PHP/PHTML/INC application files | 148 |
| Files using `mysql_*` (application only) | 20 |
| Files using `session_register()` | 7 |
| SQL injection vectors identified | 15+ entry points |
| `stripslashes()` calls (false sanitization) | 56 across 18 files |
| `include`/`require` statements | 139 across 44 files |
| `global $` declarations (application only) | 8 files |
| Database tables | 22+ |
| Admin interface files | 41 (`admin/` 17 + `madmin/` 24) |
| VIP user feature files | 26 |
