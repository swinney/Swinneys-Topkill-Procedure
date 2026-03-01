## Why

The legacy Swinney.org codebase is dead on arrival — 60+ fatal `mysql_*` calls removed in PHP 7, 20 `session_register()` calls removed in PHP 5.4, and a PEAR DB dependency chain that cannot run on the current PHP 8.2 container. Rather than patching a corpse, Phase A (per MODERNIZATION.md) bootstraps an entirely new application skeleton on modern infrastructure so that subsequent phases can port features onto a working foundation.

## What Changes

- **New Docker dev environment**: PHP 8.3-FPM Alpine, Nginx 1.27 front-controller, MySQL 8.4 with healthchecks, Mailpit for email capture — replacing the current Bitnami-based setup
- **Composer + PSR-4 autoloading**: `Swinsite\` namespace under `src/`, replacing the PEAR include-path approach and `lib/Swinsite/` manual requires
- **Slim 4 application bootstrap**: Front controller at `public/index.php`, PHP-DI container, route definitions, middleware stack (session, CSRF, error handling)
- **Twig 3 template engine**: `templates/layout.twig` master layout and `404.twig` error page, replacing the `.inc` include chain
- **PDO Database service**: `src/Service/Database.php` with prepared statements, replacing PEAR DB and raw `mysql_*` calls
- **Phinx migration framework**: Baseline migration creating the 5-table MVP schema (user, articles_info, articles_text, comments, categories) with InnoDB + foreign keys
- **Developer tooling**: Makefile with `make up/down/fresh/shell/db/migrate/seed/logs/xdebug/test`, `.env` configuration, Xdebug 3.3 support
- **BREAKING**: Legacy `web/` directory is no longer the web root — `public/` replaces it. The old PEAR-based code under `web/journals/` remains untouched but is not served.

## Capabilities

### New Capabilities
- `docker-dev-env`: Docker Compose dev environment with PHP 8.3-FPM, Nginx front-controller, MySQL 8.4, Mailpit, and Makefile tooling
- `app-bootstrap`: Slim 4 application skeleton — front controller, DI container, route definitions, middleware stack, Twig rendering, PDO database service
- `schema-migrations`: Phinx migration framework with baseline migration creating the 5-table MVP schema

### Modified Capabilities
_(none — this is a greenfield skeleton alongside the legacy code)_

## Impact

- **Docker**: Replaces current `docker-compose.yml`, `phpfpm.Dockerfile`, and all configs under `etc/`. New configs under `docker/`.
- **Dependencies**: Adds `composer.json` with 10 runtime packages + PHPUnit dev dependency
- **Directory structure**: Creates `public/`, `src/`, `templates/`, `config/`, `db/migrations/`, `db/seeds/`, `docker/`
- **Legacy code**: Untouched. `web/`, `lib/`, `db/mkdb.sql` remain in place. Legacy and new stack coexist until Phase B+ ports features.
- **Environment**: New `.env` / `.env.example` files with database credentials and app config
