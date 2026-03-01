## ADDED Requirements

### Requirement: Slim 4 front controller handles all requests
The system SHALL have a single entry point at `public/index.php` that bootstraps the Slim 4 application, loads the DI container, registers middleware, defines routes, and runs the app. No other PHP files SHALL exist in `public/`.

#### Scenario: Application boots successfully
- **WHEN** a GET request is made to `http://localhost/`
- **THEN** the Slim 4 app boots, resolves the route, and returns an HTTP response with status 200

#### Scenario: Unknown routes return 404
- **WHEN** a GET request is made to `http://localhost/nonexistent-page`
- **THEN** the app returns HTTP 404 and renders `templates/404.twig`

### Requirement: PHP-DI container provides dependency injection
The system SHALL use PHP-DI with the Slim Bridge (`php-di/slim-bridge`) as the DI container. Container definitions SHALL be in `config/container.php` and SHALL register: PDO database connection, Twig environment, session configuration, and application settings.

#### Scenario: PDO is injectable
- **WHEN** a controller constructor type-hints `\PDO`
- **THEN** PHP-DI injects a configured PDO instance connected to the MySQL container

#### Scenario: Twig is injectable
- **WHEN** a controller constructor type-hints `\Twig\Environment`
- **THEN** PHP-DI injects a Twig environment configured with `templates/` as the template directory

### Requirement: Route definitions cover all 20 MVP endpoints
The system SHALL define routes in `config/routes.php` for all 20 endpoints specified in MVP-DESIGN.md Section 4. Phase A route handlers SHALL return placeholder responses (rendered Twig template or plain text). Routes SHALL be grouped by authentication level: public, auth-required, admin-required.

#### Scenario: Public routes are accessible
- **WHEN** an unauthenticated GET request is made to `/`
- **THEN** the app returns HTTP 200 with rendered content

#### Scenario: All 20 routes are registered
- **WHEN** the Slim app boots
- **THEN** the router has exactly 20 route definitions matching the MVP route map

### Requirement: Middleware stack is configured
The system SHALL configure Slim middleware in `config/middleware.php` in this order (outermost first): error handling, session start, CSRF protection (Slim CSRF), routing, body parsing. CSRF tokens SHALL be available in all Twig templates.

#### Scenario: CSRF token is present in forms
- **WHEN** a Twig template renders `{{ csrf.keys.name }}` and `{{ csrf.keys.value }}`
- **THEN** valid CSRF token fields are output as hidden inputs

#### Scenario: POST without CSRF token is rejected
- **WHEN** a POST request is made without a valid CSRF token
- **THEN** the app returns HTTP 403

### Requirement: Twig renders templates with layout inheritance
The system SHALL configure Twig 3 with `templates/` as the template directory and auto-escaping enabled. A master layout (`templates/layout.twig`) SHALL define blocks: `head`, `nav`, `sidebar`, `content`, `footer`. Child templates SHALL extend the layout via `{% extends 'layout.twig' %}`.

#### Scenario: Layout renders with all blocks
- **WHEN** the home route renders a template that extends `layout.twig`
- **THEN** the response contains the HTML structure from layout.twig with the child's content block filled

#### Scenario: Auto-escaping is active
- **WHEN** a Twig variable contains `<script>alert('xss')</script>`
- **THEN** the output is HTML-escaped: `&lt;script&gt;alert(&#039;xss&#039;)&lt;/script&gt;`

### Requirement: Database service wraps PDO with convenience methods
The system SHALL provide `src/Service/Database.php` with methods: `query(string $sql, array $params): PDOStatement`, `getRow(string $sql, array $params): ?array`, `getAll(string $sql, array $params): array`. All queries SHALL use prepared statements. The service SHALL connect using credentials from environment variables (`DB_HOST`, `DB_NAME`, `DB_USER`, `DB_PASSWORD`).

#### Scenario: Database connects to MySQL
- **WHEN** the Database service is instantiated
- **THEN** a PDO connection to `so_mysql` is established using `.env` credentials with `ERRMODE_EXCEPTION` and `FETCH_ASSOC` defaults

#### Scenario: Prepared statements prevent SQL injection
- **WHEN** `query('SELECT * FROM user WHERE username = ?', ["admin'; DROP TABLE user; --"])` is called
- **THEN** the parameter is safely bound and no SQL injection occurs

### Requirement: Application settings loaded from environment
The system SHALL load configuration from `.env` via `vlucas/phpdotenv` in `config/settings.php`. Settings SHALL include: database DSN components, app environment (`development`/`production`), app URL, mail host/port, and Twig cache setting (disabled in development).

#### Scenario: Settings reflect .env values
- **WHEN** the app boots with `DB_HOST=so_mysql` in `.env`
- **THEN** `$settings['db']['host']` equals `so_mysql`

### Requirement: Composer autoloading with PSR-4
The system SHALL use Composer PSR-4 autoloading with namespace `Swinsite\` mapped to `src/`. The `composer.json` SHALL declare all runtime dependencies (Slim 4, PSR-7, PHP-DI, Twig, phpdotenv, Phinx, Slim CSRF, Slim Flash) and PHPUnit as a dev dependency.

#### Scenario: Autoloading resolves classes
- **WHEN** `new \Swinsite\Service\Database(...)` is used in code
- **THEN** Composer autoloads `src/Service/Database.php` without manual `require` statements
