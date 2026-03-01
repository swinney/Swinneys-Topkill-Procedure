## ADDED Requirements

### Requirement: Phinx migration framework is configured
The system SHALL include a Phinx configuration file at `db/phinx.php` that reads database credentials from environment variables. Migration files SHALL be stored in `db/migrations/`. Seed files SHALL be stored in `db/seeds/`. Phinx SHALL be executable via `vendor/bin/phinx` or `make migrate`.

#### Scenario: Phinx connects to MySQL
- **WHEN** `make migrate` is run
- **THEN** Phinx connects to the MySQL container using credentials from `.env` and applies pending migrations

#### Scenario: Phinx rollback works
- **WHEN** `make rollback` is run
- **THEN** the last applied migration is reversed

### Requirement: Baseline migration creates MVP schema
The system SHALL include a baseline migration that creates all 5 MVP tables: `user`, `categories`, `articles_info`, `articles_text`, `comments`. All tables SHALL use InnoDB engine with `utf8mb4` charset. Foreign key constraints SHALL enforce referential integrity.

#### Scenario: Migration creates user table
- **WHEN** the baseline migration runs
- **THEN** the `user` table exists with columns: `user_id` (PK, auto-increment), `username` (VARCHAR(30), UNIQUE, NOT NULL), `email` (VARCHAR(100)), `password_hash` (VARCHAR(255), nullable for legacy password reset), `ip_addr` (VARCHAR(45)), `is_admin` (TINYINT(1), default 0), `created_at` (TIMESTAMP, default CURRENT_TIMESTAMP)

#### Scenario: Migration creates categories table
- **WHEN** the baseline migration runs
- **THEN** the `categories` table exists with columns: `cat_id` (PK, auto-increment), `name` (VARCHAR(40))

#### Scenario: Migration creates articles_info table
- **WHEN** the baseline migration runs
- **THEN** the `articles_info` table exists with columns: `article_id` (PK, auto-increment), `user_id` (FK → user.user_id, NOT NULL), `category_id` (FK → categories.cat_id), `title` (VARCHAR(255)), `blurb` (TEXT), `status` (TINYINT(1)), `keywords` (VARCHAR(255)), `num_comments` (INT, default 0), `num_hits` (INT, default 0), `ip_addr` (VARCHAR(45)), `created_at` (TIMESTAMP, default CURRENT_TIMESTAMP)

#### Scenario: Migration creates articles_text table
- **WHEN** the baseline migration runs
- **THEN** the `articles_text` table exists with 1:1 relationship to `articles_info`: `article_id` (PK, FK → articles_info.article_id), `text` (MEDIUMTEXT)

#### Scenario: Migration creates comments table
- **WHEN** the baseline migration runs
- **THEN** the `comments` table exists with columns: `comment_id` (PK, auto-increment), `article_id` (FK → articles_info.article_id, NOT NULL), `user_id` (FK → user.user_id, NOT NULL), `comment` (TEXT), `status` (TINYINT(1)), `ip_addr` (VARCHAR(45)), `created_at` (TIMESTAMP, default CURRENT_TIMESTAMP)

#### Scenario: Foreign keys enforce integrity
- **WHEN** an INSERT into `articles_info` references a non-existent `user_id`
- **THEN** the database rejects the insert with a foreign key constraint violation

### Requirement: FULLTEXT index on articles for search
The baseline migration SHALL create a FULLTEXT index on `articles_info.title` and `articles_info.keywords`, and a FULLTEXT index on `articles_text.text` to support `MATCH() AGAINST()` search queries.

#### Scenario: FULLTEXT search works on article titles
- **WHEN** `SELECT * FROM articles_info WHERE MATCH(title, keywords) AGAINST('test')` is executed after data exists
- **THEN** the query uses the FULLTEXT index and returns matching rows

### Requirement: Schema rollback removes all tables
The baseline migration SHALL support rollback by dropping all 5 tables in reverse dependency order (comments → articles_text → articles_info → categories → user).

#### Scenario: Rollback leaves empty database
- **WHEN** `make rollback` is run after the baseline migration
- **THEN** all 5 MVP tables are dropped and `SHOW TABLES` returns empty
