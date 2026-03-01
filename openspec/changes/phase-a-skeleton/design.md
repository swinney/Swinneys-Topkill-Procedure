## Context

Swinney.org is a legacy PHP article/comment publishing platform from the early 2000s. The current codebase uses PEAR DB, `mysql_*` functions, `session_register()`, and include-based templates — all of which are removed or deprecated in PHP 7+. The app cannot run on its own PHP 8.2 container.

Phase A bootstraps a modern application skeleton alongside the legacy code. The legacy `web/` directory stays untouched. The new stack lives in `public/`, `src/`, `templates/`, and `config/`. Both coexist in the repo until Phase B+ ports features to the new stack.

Full specifications are in:
- `swindoc/docs/MVP-DESIGN.md` — scope, stack, schema, routes, templates
- `swindoc/docs/DOCKER-DEV.md` — container architecture, configs, Makefile
- `swindoc/docs/MODERNIZATION.md` — 8-phase migration plan

## Goals / Non-Goals

**Goals:**
- Working Slim 4 application that boots on Docker and renders a Twig template at `http://localhost`
- PDO database connection with prepared statement support verified against MySQL 8.4
- Phinx migration framework with baseline schema (5 tables, InnoDB, foreign keys)
- Developer experience: one-command startup (`make fresh`), Xdebug ready, query logging visible
- Middleware stack wired: session, CSRF, error handling
- Route definitions for all 20 MVP endpoints (handlers return placeholder responses)

**Non-Goals:**
- No feature implementation — controllers return "Coming soon" or render empty templates
- No data import from the 2011 SQL dump (Phase B)
- No authentication logic (Phase B) — middleware is wired but AuthController is a stub
- No legacy code modifications — `web/`, `lib/`, `db/mkdb.sql` are untouched
- No production deployment config — dev environment only
- No CI/CD pipeline

## Decisions

### 1. PHP 8.3-FPM Alpine over PHP 8.2

**Decision:** Use `php:8.3-fpm-alpine` base image.

**Rationale:** PHP 8.3 adds `json_validate()`, typed class constants, and `#[\Override]` — all useful for the new codebase. Alpine keeps the image small (~50MB vs ~400MB for Debian). The current 8.2 container is custom-built with PEAR; we start fresh.

**Alternative:** Stay on 8.2. Rejected — no reason to start a greenfield on anything but latest stable.

### 2. Slim 4 over Laravel/Symfony

**Decision:** Slim 4 micro-framework with PHP-DI and Twig.

**Rationale:** The MVP has 20 routes and 5 database tables. Laravel/Symfony bring massive overhead for a site this size. Slim 4 gives PSR-7/15/17 compliance, middleware pipeline, and dependency injection without the weight. The team can understand the entire framework in an afternoon.

**Alternative:** Laravel. Rejected — 200+ files in a fresh install for a 20-route app is absurd.

### 3. PDO over Doctrine DBAL

**Decision:** Native PDO with a thin `Database` service wrapper.

**Rationale:** 5 tables, ~15 unique queries total. Doctrine DBAL adds configuration complexity and a learning curve for zero benefit at this scale. The `Database` service provides `query()`, `getRow()`, `getAll()` convenience methods around PDO prepared statements.

**Alternative:** Doctrine DBAL. Rejected — overkill. Could revisit if schema grows significantly.

### 4. Named Docker volume over bind mount for MySQL

**Decision:** `mysql_data:` named volume instead of `./data/db/mysql` bind mount.

**Rationale:** Bind mounts for MySQL on macOS have severe performance issues due to filesystem translation (osxfs/virtiofs). Named volumes run at native speed. The current bind mount at `data/db/mysql/` has 250+ files in git status noise.

**Alternative:** Keep bind mount. Rejected — the `data/db/mysql/` directory currently pollutes git status with hundreds of binary files.

### 5. Coexistence strategy — new stack alongside legacy

**Decision:** New code in `public/`, `src/`, `templates/`, `config/`. Legacy code stays in `web/`, `lib/`.

**Rationale:** Phase A must not break the legacy code even though it can't run. Future phases may need to reference legacy code for porting logic. Clean separation means no merge conflicts between old and new.

**Alternative:** Delete legacy code. Rejected — it's the reference implementation for porting.

### 6. Phinx over raw SQL for schema management

**Decision:** Phinx migrations with a baseline migration creating all 5 MVP tables.

**Rationale:** Phinx provides version-controlled, repeatable schema changes with rollback support. The old `db/mkdb.sql` is a monolithic dump — no way to track incremental changes. Phinx integrates with Composer and runs via `make migrate`.

**Alternative:** Raw SQL files. Rejected — no rollback, no version tracking, no programmatic seeding.

### 7. Front controller pattern — single `index.php`

**Decision:** All requests route through `public/index.php`. Nginx `try_files` directive sends non-file requests to the front controller.

**Rationale:** Standard modern PHP pattern. Eliminates the legacy approach of one PHP file per page (58 scripts). Slim 4 router handles dispatch. Single entry point means one place for bootstrapping, middleware, and error handling.

## Risks / Trade-offs

| Risk | Mitigation |
|------|------------|
| Legacy code referenced during porting but Docker no longer serves `web/` | Legacy files remain in repo. Can add a temporary Nginx location block if needed for side-by-side comparison. |
| MySQL 8.4 compatibility with old data dump | Phase A uses fresh schema via Phinx. Data import (Phase B) will handle dump compatibility separately. |
| Xdebug overhead in dev | Controlled via `XDEBUG_MODE` env var — defaults to `off`. Only activates on `make xdebug`. |
| Composer dependencies pinned too loosely | Use `^` constraints (Composer default). `composer.lock` pins exact versions. |
| Mailpit not needed until email features exist | Minimal resource usage. Having it from day one means email-dependent features (password reset) work immediately when added. |

## Migration Plan

**Deploy sequence:**
1. Create new directory structure (`public/`, `src/`, `templates/`, `config/`, `docker/`, `db/migrations/`)
2. Write Docker configs (`Dockerfile`, `docker-compose.yml`, `dev.ini`, `default.conf`, `dev.cnf`)
3. Write application configs (`composer.json`, `.env`, `Makefile`, `phinx.php`)
4. Bootstrap Slim 4 app (`public/index.php`, `config/container.php`, `config/routes.php`, `config/middleware.php`, `config/settings.php`)
5. Create services (`src/Service/Database.php`)
6. Create baseline Phinx migration with 5-table schema
7. Create Twig templates (`templates/layout.twig`, `templates/404.twig`)
8. `make fresh` → verify Hello World at `http://localhost`

**Rollback:** Delete new directories. Restore old `docker-compose.yml` from git. The legacy code is never modified.

## Open Questions

None — all design decisions were resolved on 2026-03-01 (see MVP-DESIGN.md Section 11).
