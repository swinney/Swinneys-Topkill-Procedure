## 1. Directory Structure

- [x] 1.1 Create new directory tree: `public/`, `public/css/`, `public/img/`, `src/Controller/`, `src/Middleware/`, `src/Service/`, `templates/`, `templates/partials/`, `config/`, `db/migrations/`, `db/seeds/`, `docker/nginx/`, `docker/php/`, `docker/mysql/`
- [x] 1.2 Create `.gitignore` entries for `vendor/`, `.env`, `composer.lock`, `var/cache/`

## 2. Docker Configuration

- [x] 2.1 Create `docker/php/Dockerfile` — PHP 8.3-FPM Alpine with pdo_mysql, intl, zip, opcache, Xdebug 3.5, Composer 2
- [x] 2.2 Create `docker/php/dev.ini` — error display on, opcache off, session security, Xdebug client config
- [x] 2.3 Create `docker/nginx/default.conf` — front controller routing to `public/index.php`, security headers, dotfile blocking, FastCGI to phpfpm:9000
- [x] 2.4 Create `docker/mysql/dev.cnf` — utf8mb4, query logging, skip-log-bin, fast flush settings
- [x] 2.5 Create `docker-compose.yml` — 4 services (nginx, phpfpm, mysql, mailpit), named volume, healthcheck, swinney bridge network
- [x] 2.6 Create `.env.example` and `.env` — DB credentials, app config, Xdebug mode, mail settings

## 3. Composer & Autoloading

- [x] 3.1 Create `composer.json` — PSR-4 `Swinsite\` → `src/`, all runtime deps (slim/slim, slim/psr7, slim/csrf, slim/flash, php-di/php-di, php-di/slim-bridge, twig/twig, vlucas/phpdotenv, robmorgan/phinx), PHPUnit dev dep
- [x] 3.2 Run `composer install` inside PHP container to generate `vendor/` and autoload files

## 4. Application Bootstrap

- [x] 4.1 Create `config/settings.php` — load `.env` via phpdotenv, return settings array (db, app, twig, mail)
- [x] 4.2 Create `config/container.php` — PHP-DI definitions for PDO, Twig\Environment, settings
- [x] 4.3 Create `config/middleware.php` — register error handling, session start, CSRF, routing, body parsing middleware on the Slim app
- [x] 4.4 Create `config/routes.php` — define all 20 MVP routes with placeholder handlers returning Twig-rendered responses or plain text
- [x] 4.5 Create `public/index.php` — Slim 4 front controller: require autoload, load settings, build container, create app, add middleware, add routes, run

## 5. Services

- [x] 5.1 Create `src/Service/Database.php` — PDO wrapper with `query()`, `getRow()`, `getAll()` methods using prepared statements. **[SECURITY-CRITICAL]** All parameters bound via prepared statements.

## 6. Templates

- [x] 6.1 Create `templates/layout.twig` — master HTML layout with `head`, `nav`, `sidebar`, `content`, `footer` blocks, CSRF token globals, 90s-era aesthetic structure
- [x] 6.2 Create `templates/404.twig` — extends layout, displays "Page not found" in content block
- [x] 6.3 Create `templates/home.twig` — extends layout, displays "Hello World" / welcome placeholder in content block

## 7. Database Migrations

- [x] 7.1 Create `db/phinx.php` — Phinx config reading DB credentials from environment variables, pointing to `db/migrations/` and `db/seeds/`
- [x] 7.2 Create baseline migration `db/migrations/` — creates 5 tables (user, categories, articles_info, articles_text, comments) with InnoDB, utf8mb4, foreign keys, FULLTEXT indexes on articles_info(title, keywords) and articles_text(text). Rollback drops in reverse dependency order.

## 8. Developer Tooling

- [x] 8.1 Create `Makefile` — targets: up, down, build, fresh, shell, install, db, migrate, seed, rollback, logs, logs-php, logs-sql, xdebug, test, test-coverage

## 9. Smoke Test

- [x] 9.1 Run `make fresh` — verify all containers start, Composer installs, migrations run
- [x] 9.2 Verify `http://localhost` returns 200 with rendered Twig layout
- [x] 9.3 Verify `http://localhost/nonexistent` returns 404 with rendered 404.twig
- [x] 9.4 Verify `make db` connects to MySQL and `SHOW TABLES` lists all 5 MVP tables
