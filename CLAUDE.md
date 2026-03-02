# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Swinney.org — a legacy article/comment publishing platform from the early 2000s, resurrected with PHP 8 and Docker. "Night of the Living Dead but for 90's websites."

## Build & Run

```bash
# Start all services (Nginx, PHP-FPM, MySQL)
docker-compose up -d

# Rebuild PHP-FPM container after Dockerfile changes
docker-compose up -d --build phpfpm

# Access the site
open http://localhost

# Connect to MySQL directly
mysql -h 127.0.0.1 -u root -pbananas swinney
```

There are no tests, linters, or CI pipelines in this project.

## Architecture

### Docker Services
- **so_nginx** — Bitnami Nginx on ports 80/443, serves from `/app` (read-only mount of `./web`)
- **so_phpfmp** — PHP 8.2-FPM (custom Dockerfile: `phpfpm.Dockerfile`), PEAR extensions: DB, MDB2, MDB2_Driver_mysqli
- **so_mysql** — MySQL, initialized from `db/swinney.db.2011.02.16.sql`, data persisted in `data/db/mysql/`

### Request Flow
Nginx (port 80) → FastCGI to PHP-FPM (port 9000) → PHP scripts include `global.php` → PEAR DB connection → Swinsite ORM classes → template includes → HTML response

### Key Directories
- `web/journals/` — Main application: entry points (`index.php`, `article.php`, `comments.php`, `login.php`, `search.php`), plus `admin/` and `madmin/` for admin tools
- `web/journals/templates/` — Include-based template system (`.inc` files): `template.inc` is the master layout, pulls in `top.inc`, `footer.inc`, `rollcall.inc`, etc.
- `web/journals/global.php` — Central initialization (~625 lines): constants, DB connection, session setup, auth helpers, utility functions
- `web/journals/local_conf.php` — Environment config: paths, DB credentials, URL base
- `lib/Swinsite/` — ORM layer: `Articles.php`, `User.php`, `Multi.php`, `Bozos.php`, `File.php`, plus `Persistent/` base classes and `DBPeer/` database peers
- `web/chat/` — Chat/thoughts feature (`.phtml` files)
- `db/mkdb.sql` — Database schema definition
- `etc/` — Nginx config (`etc/nginx/`), PHP config (`etc/php/php.ini`), PHP-FPM config (`etc/phpfpm/`)

### Application Patterns

**Page structure:** Each page script sets variables (`$title`, `$into_template`), includes `global.php` for initialization, then includes `templates/template.inc` which assembles the master layout around the content.

**Database access:** Uses PEAR DB with `mysqli` DSN. Most queries are direct SQL in page scripts or the `Swinsite\Articles` class. The ORM in `lib/Swinsite/Persistent/` provides a peer-based pattern (`DBPeer.php`, `DBSetPeer.php`) for CRUD on `User` and `Bozos` objects.

**Session/auth:** PHP sessions with `$_SESSION['authenticated_username']` and `$_SESSION['authenticated_user_id']`. The `is_auth()` function in `global.php` gates protected pages.

**Container paths:** Inside containers, the web root is `/app` (mapped from `./web`). The Swinsite library is at `/usr/local/lib/swinney` (mapped from `./lib/Swinsite`). PEAR libs are at `/pear/share/pear`.

### Database Schema (MySQL, database: `swinney`)
Core tables: `articles_info` (metadata + PK `article_id`), `articles_text` (content body), `comments` (per-article), `user` (auth + profile), `categories`, `articles_user` (user stats), `articles_front` (featured). Supporting: `multi_info`/`multi_articles` (article series), `user_bozo` (ignore lists), `user_perm`/`perm_set` (permissions), `thoughts` (chat), `search_words`.

## Verification Standard

All code verification MUST use Intelephense LSP diagnostics, not grep/rg. This applies to OpenSpec specs, tasks, and all post-implementation checks.

- **P1010** — undefined function (e.g., removed `mysql_*`, `session_register`, `ereg_replace`)
- **P1008** — undefined variable (e.g., missing `global $db`)
- **P1011** — undefined constant (e.g., missing `define('OK', true)`)
- **P1006** — type mismatch
- **P1014** — undefined property

Use grep/rg only for text/pattern searches (comments, strings, config values) where LSP has no coverage.
