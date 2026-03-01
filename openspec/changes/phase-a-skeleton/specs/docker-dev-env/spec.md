## ADDED Requirements

### Requirement: PHP-FPM container runs PHP 8.3 on Alpine
The system SHALL provide a PHP-FPM container built from `php:8.3-fpm-alpine` with extensions `pdo_mysql`, `intl`, `zip`, and `opcache` installed. Xdebug 3.3 SHALL be installed but disabled by default (controlled via `XDEBUG_MODE` environment variable). Composer 2 SHALL be available inside the container.

#### Scenario: PHP container starts with correct version
- **WHEN** `docker compose up -d` is run
- **THEN** the `so_phpfpm` container starts and `php -v` reports PHP 8.3.x

#### Scenario: PDO MySQL extension is available
- **WHEN** `docker compose exec phpfpm php -m` is run
- **THEN** the output includes `pdo_mysql`

#### Scenario: Xdebug is off by default
- **WHEN** `docker compose up -d` is run without setting `XDEBUG_MODE`
- **THEN** `php -m` does not list xdebug as active and there is no performance overhead

#### Scenario: Xdebug activates on demand
- **WHEN** `make xdebug` is run (sets `XDEBUG_MODE=debug`)
- **THEN** the PHP container restarts with Xdebug enabled, listening on port 9003

### Requirement: Nginx container serves front controller
The system SHALL provide an Nginx 1.27 Alpine container that serves `public/` as the web root. All non-file requests SHALL be routed to `public/index.php` via `try_files`. Security headers (`X-Content-Type-Options`, `X-Frame-Options`, `Referrer-Policy`) SHALL be set on all responses. Dotfiles SHALL be blocked.

#### Scenario: Front controller routing works
- **WHEN** a request is made to `http://localhost/any-path`
- **THEN** Nginx forwards the request to `public/index.php` via FastCGI to `phpfpm:9000`

#### Scenario: Static assets are served directly
- **WHEN** a request is made to `http://localhost/css/main.css` and the file exists
- **THEN** Nginx serves the file directly without invoking PHP

#### Scenario: Dotfiles are blocked
- **WHEN** a request is made to `http://localhost/.env`
- **THEN** Nginx returns 403 Forbidden

### Requirement: MySQL container with healthcheck
The system SHALL provide a MySQL 8.4 container using a named Docker volume (`mysql_data`) for data persistence. The container SHALL have a healthcheck using `mysqladmin ping`. Binary logging SHALL be disabled. Query logging SHALL be enabled for development. The charset SHALL be `utf8mb4`.

#### Scenario: MySQL is healthy before PHP starts
- **WHEN** `docker compose up -d` is run
- **THEN** the `so_phpfpm` container waits for `so_mysql` to pass its healthcheck before starting

#### Scenario: Data persists across restarts
- **WHEN** `docker compose down` then `docker compose up -d` is run
- **THEN** all database data is preserved in the `mysql_data` named volume

#### Scenario: Fresh start destroys data
- **WHEN** `docker compose down -v` is run
- **THEN** the `mysql_data` volume is removed and the next `up` starts with an empty database

### Requirement: Mailpit captures outbound email
The system SHALL provide a Mailpit container accessible at `http://localhost:8025` (web UI) and `localhost:1025` (SMTP). Application email configuration SHALL point to Mailpit so no real emails are sent during development.

#### Scenario: Mailpit web UI is accessible
- **WHEN** `docker compose up -d` is run
- **THEN** `http://localhost:8025` shows the Mailpit inbox

### Requirement: Makefile provides developer shortcuts
The system SHALL provide a Makefile with targets: `up`, `down`, `build`, `fresh`, `shell`, `install`, `db`, `migrate`, `seed`, `rollback`, `logs`, `logs-php`, `logs-sql`, `xdebug`, `test`, `test-coverage`.

#### Scenario: make fresh bootstraps from scratch
- **WHEN** `make fresh` is run
- **THEN** all containers are rebuilt, Composer dependencies installed, migrations run, and seeds applied

#### Scenario: make shell opens PHP container
- **WHEN** `make shell` is run
- **THEN** an interactive shell session opens inside the `so_phpfpm` container

### Requirement: Environment configuration via .env
The system SHALL use a `.env` file for all environment-specific configuration (database credentials, app URL, Xdebug mode, mail settings). A `.env.example` SHALL be provided as a template. The `.env` file SHALL NOT be committed to git.

#### Scenario: Docker reads env vars from .env
- **WHEN** `docker compose up -d` is run with a valid `.env` file
- **THEN** the MySQL container uses `DB_NAME`, `DB_USER`, `DB_PASSWORD`, and `DB_ROOT_PASSWORD` from `.env`
