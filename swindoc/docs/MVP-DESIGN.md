# MVP Design: Swinney.org Relaunch

> **Status:** Draft — pending decisions on open questions
> **Context:** The app is dead on arrival (60+ fatal `mysql_*` calls on PHP 8). Not hosted. This is a ground-up relaunch, not an incremental fix.
> **Approach:** Skip the bridge strategy. Go directly to a modern stack. Preserve the original publishing-platform soul — just make it work and make it safe.

---

## 1. MVP Scope

### What Stays

The original Swinney.org was an article/comment publishing platform. The MVP preserves that core identity.

| Area | Feature | Scripts (original) |
|------|---------|-------------------|
| **Public** | Homepage — recent article listing | `index.php`, `insert_articles.inc` |
| | Article view with comments | `article.php`, `insert_comments.php` |
| | Search (articles + comments) | `search.php` |
| | Roll call (active writers sidebar) | `get_rollcall()` in `global.php` |
| | User profile / author pages | `userpages.php`, `info_user.php` |
| **Auth** | Login | `login.php`, `process_login.php` |
| | Register | `submit_register.php`, `process_register.php` |
| | Logout | `process_logout.php` |
| **Authenticated** | Submit article | `submit_article.php`, `process_article.php` |
| | Post comment (auth required) | `submit_comment.php`, `process_comment.php` |
| **Admin** | Article CRUD (status, edit, delete) | `admin/listcontent.php`, `admin/edit_article.php` |
| | Comment moderation | `admin/edit_comments.php`, `admin/admin_comments.php` |
| | User list | `admin/users.php` |

### What's Cut

| Feature | Files Killed | Why |
|---------|-------------|-----|
| Bozo/ignore system | `Bozos.php`, `BozosPeer.php`, `process_bozo_id.php`, `submit_bozo.phtml` | Complexity for an MVP. Add later if needed. |
| Thoughts/chat | `web/chat/` (4 files), `insert_thought.php`, `submit_thought.php` | Separate feature. Not core publishing. |
| Multi-article series | `Multi.php`, `multi_info.php`, VIP multi files (8 files) | Power feature. Defer. |
| VIP dashboard | `web/journals/vip/` (26 files) | Collapsed into basic user profile + admin. |
| Master admin (madmin) | `web/journals/madmin/` (24 files) | Redundant with `admin/`. One admin is enough. |
| Image/file upload | `File.php`, `process_image.php`, `submit_image.php` | Security-sensitive. Build properly later. |
| Category bitmask system | `process_category.php`, `submit_category.php` | Replace with simple `category_id` FK. |
| reCAPTCHA v1 | In `process_login.php`, `process_register.php` | Dead service (recaptcha.net is gone). Replace with honeypot + rate limiting. |
| Binary converter | `bin.php`, `bin_converter.php` | Easter egg. Not core. |
| FAQ | `faq.php` | Static content. Can be a Twig template later. |
| Alpha listing | `alpha.php` | Niche. Defer. |
| PEAR DB | All of `pear/`, `swinlib/` | Replaced entirely by PDO. |

**Net result:** ~58 original scripts collapse into ~12 Slim route handlers + ~12 Twig templates.

---

## 2. Target Stack

```
┌─────────────────────────────────────────────────────────────────┐
│                         BROWSER                                 │
└──────────────────────────────┬──────────────────────────────────┘
                               │
┌──────────────────────────────▼──────────────────────────────────┐
│                      Nginx (so_nginx)                           │
│                 static files + reverse proxy                    │
└──────────────────────────────┬──────────────────────────────────┘
                               │ FastCGI :9000
┌──────────────────────────────▼──────────────────────────────────┐
│                   PHP 8.3-FPM (so_phpfpm)                       │
│                                                                  │
│  ┌────────────────────────────────────────────────────────────┐  │
│  │                 Slim 4 Front Controller                     │  │
│  │          public/index.php → App → Middleware → Route        │  │
│  └──────┬─────────────────┬────────────────────┬──────────────┘  │
│         │                 │                    │                  │
│  ┌──────▼───────┐  ┌─────▼──────────┐  ┌─────▼──────────┐      │
│  │  Middleware   │  │  Controllers   │  │    Twig 3      │      │
│  │              │  │               │  │               │      │
│  │ • Session    │  │ • HomeCtrl    │  │ • layout.twig │      │
│  │ • Auth gate  │  │ • ArticleCtrl │  │ • home.twig   │      │
│  │ • CSRF       │  │ • CommentCtrl │  │ • article.twig│      │
│  │ • Rate limit │  │ • AuthCtrl    │  │ • search.twig │      │
│  │              │  │ • SearchCtrl  │  │ • login.twig  │      │
│  │              │  │ • UserCtrl    │  │ • register.twg│      │
│  │              │  │ • AdminCtrl   │  │ • admin/*.twig│      │
│  └──────────────┘  └───────┬───────┘  └──────────────┘      │
│                            │                                     │
│                     ┌──────▼───────┐                             │
│                     │     PDO      │                             │
│                     │  (prepared   │                             │
│                     │  statements) │                             │
│                     └──────┬───────┘                             │
└────────────────────────────┼─────────────────────────────────────┘
                             │
┌────────────────────────────▼─────────────────────────────────────┐
│                     MySQL (so_mysql)                              │
│               InnoDB • Foreign Keys • Indexes                    │
└──────────────────────────────────────────────────────────────────┘
```

### Component Choices

| Layer | Choice | Rationale |
|-------|--------|-----------|
| **Runtime** | PHP 8.3+ with `declare(strict_types=1)` | Current LTS. Strict types catch bugs at runtime. |
| **Framework** | Slim 4 | Micro-framework. Adds PSR-7, middleware, DI — without imposing MVC scaffolding on a small app. |
| **DI Container** | PHP-DI | Auto-wiring. Controllers declare what they need, container provides it. |
| **Templates** | Twig 3 | Auto-escaping kills XSS by default. Template inheritance replaces the `.inc` include chains. |
| **Database** | PDO (native) | No ORM. This app has ~15 queries total. Prepared statements are sufficient. |
| **Auth** | `password_hash()` / `password_verify()` | Native PHP. Argon2ID. No external auth library needed at this scale. |
| **Sessions** | Native PHP sessions | With secure cookie params via Slim middleware. |
| **Autoloading** | Composer PSR-4 | `Swinsite\\` namespace for any reusable classes. |
| **Config** | `vlucas/phpdotenv` | `.env` file. Credentials never in code. |
| **Migrations** | Phinx | Versioned schema changes. `phinx migrate` from zero to production. |
| **Containers** | Docker Compose (existing) | Keep `so_nginx`, `so_phpfpm`, `so_mysql`. Update Dockerfile for PHP 8.3. |

### What We're NOT Doing

- **No SPA/frontend framework.** The table-based HTML aesthetic is the product.
- **No full ORM (Doctrine/Eloquent).** ~15 queries don't justify the abstraction.
- **No API layer.** Server-rendered HTML. An API can come later.
- **No external auth service.** Native PHP sessions + password_hash is right-sized.

---

## 3. Data Model

### MVP Schema (5 tables)

```
┌──────────────────┐       ┌──────────────────────┐
│      user        │       │    articles_info      │
├──────────────────┤       ├──────────────────────┤
│ user_id    PK AI │◀──┐   │ article_id    PK AI  │
│ username   UNQ   │   ├───│ user_id       FK     │
│ email            │   │   │ category_id   FK ────│───┐
│ password_hash    │   │   │ title                │   │
│ ip_addr  V(45)   │   │   │ blurb                │   │
│ is_admin TINY(1) │   │   │ status       TINY(1) │   │
│ created_at TS    │   │   │ keywords             │   │
└──────────────────┘   │   │ num_comments  INT    │   │
                       │   │ num_hits      INT    │   │
┌──────────────────┐   │   │ ip_addr      V(45)  │   │
│    comments      │   │   │ created_at   TS     │   │
├──────────────────┤   │   └──────────┬───────────┘   │
│ comment_id PK AI │   │              │               │
│ article_id FK ───│───│──────────────┘               │
│ user_id    FK ───│───┘                              │
│ comment    TEXT   │          ┌──────────────────┐    │
│ status   TINY(1) │          │  articles_text   │    │
│ ip_addr  V(45)   │          ├──────────────────┤    │
│ created_at TS    │          │ article_id PK FK │    │
└──────────────────┘          │ text  MEDIUMTEXT │    │
                              └──────────────────┘    │
                                                      │
                              ┌──────────────────┐    │
                              │   categories     │    │
                              ├──────────────────┤    │
                              │ cat_id    PK AI  │◀───┘
                              │ name     V(40)   │
                              └──────────────────┘
```

### Changes from Original Schema

| Original | MVP | Why |
|----------|-----|-----|
| `password TEXT` with `crypt()` | `password_hash VARCHAR(255)` with Argon2ID | Modern hashing. 8-char DES limit is a joke. |
| `category BIGINT` (bitmask) | `category_id INT` (FK) | Bitmask limits to 32 categories, requires bitwise SQL. Simple FK is cleaner. |
| `user_perm` + `perm_set` tables | `is_admin TINYINT(1)` column | Two tables for a boolean. This app has users and admins, that's it. |
| `ip_addr TEXT` | `ip_addr VARCHAR(45)` | IPv6 max is 45 chars. TEXT is wasteful. |
| No timestamps | `created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP` | Every table gets one. |
| `MyISAM` engine | `InnoDB` | Transactions, foreign keys, crash recovery. |
| No foreign keys | FK constraints on `user_id`, `article_id`, `category_id` | Data integrity enforced by the database, not PHP code. |
| `articles_comments` table | Dropped | Redundant with `articles_info.num_comments`. |
| `articles_user` table | Dropped | Redundant with `JOIN` on `articles_info`. |
| `articles_front` table | Dropped | Featured articles can be a `status` flag or deferred. |
| `username` column on `comments` | Kept (denormalized) | Avoids a JOIN on every comment render. Populated from session on insert. |

### Article Status Codes

Preserving the original meaning from `pretty_status()` in `global.php`:

| Status | Meaning | Visible? |
|--------|---------|----------|
| 0 | New / pending review | Admin only |
| 1 | Published | Public |
| 2 | Rejected | Admin only |
| 3 | Archived | Public (no homepage) |
| 4 | Deleted | Nobody |

---

## 4. Route Map

```
METHOD  PATH                        HANDLER              AUTH     NOTES
══════  ══════════════════════════  ═══════════════════  ═══════  ══════════════════

GET     /                           HomeController       public   Article listing
GET     /article/{id}               ArticleController    public   Article + comments
GET     /search                     SearchController     public   Search form + results
GET     /user/{username}            UserController       public   Author's articles
GET     /rollcall                   UserController       public   All active writers

GET     /login                      AuthController       public   Login form
POST    /login                      AuthController       public   Process login
GET     /register                   AuthController       public   Register form
POST    /register                   AuthController       public   Process register
GET     /logout                     AuthController       auth     Destroy session

GET     /submit                     ArticleController    auth     Article form
POST    /submit                     ArticleController    auth     Process article
POST    /comment                    CommentController    auth     Process comment

GET     /admin                      AdminController      admin    Dashboard
GET     /admin/articles             AdminController      admin    Article list
GET     /admin/articles/{id}/edit   AdminController      admin    Edit form
POST    /admin/articles/{id}        AdminController      admin    Save edits
POST    /admin/articles/{id}/status AdminController      admin    Change status
GET     /admin/comments             AdminController      admin    Comment list
POST    /admin/comments/{id}        AdminController      admin    Moderate comment
GET     /admin/users                AdminController      admin    User list
```

**Total: 20 routes** replacing 58 original scripts.

### Middleware Stack

```
Every request:
┌──────────────────────────────────────────────────────┐
│  1. Session middleware   (start session, set params) │
│  2. CSRF middleware      (generate/validate tokens)  │
│  3. Rate limit middleware (throttle by IP)           │
└──────────────────────────────────────────────────────┘

Route group: /submit, /comment, /logout
┌──────────────────────────────────────────────────────┐
│  4. Auth middleware      (require logged-in user)    │
└──────────────────────────────────────────────────────┘

Route group: /admin/*
┌──────────────────────────────────────────────────────┐
│  5. Admin middleware     (require is_admin = 1)      │
└──────────────────────────────────────────────────────┘
```

---

## 5. Template Hierarchy

Twig template inheritance replaces the old `.inc` include chain.

```
templates/
├── layout.twig              ◀── Master layout (replaces template.inc)
│   ├── {% block head %}
│   ├── {% block nav %}      ◀── top.inc + swinney.req
│   ├── {% block sidebar %}  ◀── rollcall.inc
│   ├── {% block content %}  ◀── $into_template variable
│   └── {% block footer %}   ◀── footer.inc
│
├── home.twig                ◀── extends layout, block content = article listing
├── article.twig             ◀── extends layout, article + comments + comment form
├── search.twig              ◀── extends layout, search form + results
├── user.twig                ◀── extends layout, author profile + articles
├── rollcall.twig            ◀── extends layout, all active writers
│
├── auth/
│   ├── login.twig           ◀── extends layout, login form
│   └── register.twig        ◀── extends layout, registration form
│
├── submit/
│   └── article.twig         ◀── extends layout, article submission form
│
├── admin/
│   ├── layout.twig          ◀── admin-specific layout (simpler nav)
│   ├── dashboard.twig
│   ├── articles.twig        ◀── article list with status/edit controls
│   ├── article_edit.twig    ◀── edit form
│   ├── comments.twig        ◀── comment moderation list
│   └── users.twig           ◀── user list
│
└── partials/
    ├── article_card.twig    ◀── reusable article summary (title, blurb, author, date)
    ├── comment.twig         ◀── single comment block
    ├── pagination.twig      ◀── page nav
    └── flash.twig           ◀── success/error messages
```

### Auto-Escaping

Twig escapes all `{{ variable }}` output by default. Raw HTML (for article body content) uses the explicit `{{ text|raw }}` filter — making it a conscious decision, not an accident.

---

## 6. Security Model

### Attack Surface → Defense Matrix

```
THREAT                    DEFENSE                           LAYER
════════════════════════  ══════════════════════════════    ═════════════

SQL injection             PDO prepared statements           Database
                          Zero string interpolation
                          All queries use ? placeholders

XSS (reflected)           Twig auto-escaping                Template
                          {{ var }} escapes by default
                          |raw only for trusted article body

XSS (stored)              htmlspecialchars() on input        Controller
                          Twig escaping on output            Template
                          Comments are plain text, not HTML

CSRF                      Slim CSRF middleware               Middleware
                          Token in every POST form
                          Validated server-side

Brute force login         Rate limiting: 5 attempts/15 min   Middleware
                          Account lockout after 10 fails     Controller
                          session_regenerate_id() on login   Session

Bot registration          Honeypot hidden field              Form
                          Rate limit: 3 registrations/hour   Middleware
                          (replaces dead reCAPTCHA v1)

Comment spam              Auth required to comment           Middleware
                          Rate limit: 1 comment/30 sec       Middleware
                          No anonymous comments allowed

Password cracking         password_hash(PASSWORD_ARGON2ID)   Auth
                          Replaces crypt()/DES (8-char max)
                          Cost factor tuned to ~100ms

Session hijacking         httponly: true                      Session
                          samesite: Lax
                          secure: true (when HTTPS)
                          Regenerate ID on login

Open redirect             Whitelist redirect targets          Controller
                          Only allow relative paths

Directory traversal       Nginx serves /app as root           Nginx
                          PHP files outside webroot           Filesystem
                          No user-controlled file paths
```

### Session Configuration

```php
session_set_cookie_params([
    'lifetime' => 86400 * 30,    // 30 days (not 317 years)
    'path'     => '/',
    'domain'   => '',            // current domain (not hardcoded swinney.org)
    'secure'   => true,          // HTTPS only
    'httponly'  => true,          // no JavaScript access
    'samesite' => 'Lax',         // CSRF protection
]);
```

---

## 7. Project Structure

```
Swinneys-Topkill-Procedure/
│
├── public/                          ◀── Web root (Nginx serves from here)
│   ├── index.php                    ◀── Slim 4 front controller (ONLY PHP file here)
│   ├── css/
│   │   └── main.css                 ◀── Migrated from web/journals/main.css
│   ├── img/                         ◀── Static images from web/journals/img/
│   └── .htaccess                    ◀── Fallback if not Nginx
│
├── src/                             ◀── Application code (PSR-4: Swinsite\)
│   ├── Controller/
│   │   ├── HomeController.php
│   │   ├── ArticleController.php
│   │   ├── CommentController.php
│   │   ├── AuthController.php
│   │   ├── SearchController.php
│   │   ├── UserController.php
│   │   └── AdminController.php
│   ├── Middleware/
│   │   ├── AuthMiddleware.php
│   │   ├── AdminMiddleware.php
│   │   └── RateLimitMiddleware.php
│   └── Service/
│       ├── Database.php             ◀── PDO wrapper (connect, query, getRow, getAll)
│       └── Auth.php                 ◀── password_hash/verify, session management
│
├── templates/                       ◀── Twig templates (see Section 5)
│
├── config/
│   ├── routes.php                   ◀── All route definitions
│   ├── middleware.php               ◀── Middleware stack
│   ├── container.php                ◀── PHP-DI definitions
│   └── settings.php                 ◀── App settings (reads .env)
│
├── db/
│   ├── migrations/                  ◀── Phinx migration files
│   ├── seeds/                       ◀── Seed data (from 2011 SQL dump)
│   └── phinx.php                    ◀── Phinx config
│
├── docker/
│   ├── nginx/
│   │   ├── default.conf             ◀── Updated for public/ root
│   │   └── fastcgi_params
│   ├── php/
│   │   └── php.ini
│   └── phpfpm.Dockerfile            ◀── Updated for PHP 8.3, no PEAR
│
├── docker-compose.yml
├── composer.json
├── .env                             ◀── DB_HOST, DB_USER, DB_PASS, etc.
├── .env.example                     ◀── Template (no secrets)
├── .gitignore                       ◀── vendor/, .env, data/
│
├── swindoc/                         ◀── Project documentation (MkDocs)
├── openspec/                        ◀── Change management
└── CLAUDE.md                        ◀── AI assistant instructions
```

### Key Structural Changes

| Before | After | Why |
|--------|-------|-----|
| `web/` is the web root | `public/` is the web root | Only `index.php` is web-accessible. PHP source code is above the web root. |
| `lib/Swinsite/` with PEAR naming | `src/` with PSR-4 namespaces | `Swinsite\Controller\ArticleController` instead of manual includes. |
| `web/journals/global.php` (625 lines) | Split into `config/`, `src/Service/`, `src/Middleware/` | Each responsibility in its own file. |
| `etc/nginx/`, `etc/php/` | `docker/nginx/`, `docker/php/` | Grouped with Dockerfile. |
| `pear/`, `swinlib/` | Deleted | Replaced by Composer dependencies. |

---

## 8. Composer Dependencies

```json
{
    "require": {
        "php": ">=8.3",
        "slim/slim": "^4.0",
        "slim/psr7": "^1.0",
        "slim/csrf": "^1.0",
        "slim/flash": "^0.4",
        "php-di/php-di": "^7.0",
        "php-di/slim-bridge": "^3.0",
        "twig/twig": "^3.0",
        "vlucas/phpdotenv": "^5.0",
        "robmorgan/phinx": "^0.16"
    },
    "require-dev": {
        "phpunit/phpunit": "^11.0"
    },
    "autoload": {
        "psr-4": {
            "Swinsite\\": "src/"
        }
    }
}
```

**Total new dependencies: 9 runtime + 1 dev.** No bloat.

---

## 9. Data Migration Strategy

The 2011 SQL dump (`db/swinney.db.2011.02.16.sql`) contains real articles and comments. Migration path:

```
Step 1: Phinx creates the new schema (clean InnoDB tables with FKs)

Step 2: Migration seed script:
  ┌─────────────────────────────────────────────────────────────┐
  │  Old user table                    New user table            │
  │  ─────────────                     ──────────────            │
  │  user_id          ──────────────▶  user_id                  │
  │  username         ──────────────▶  username                 │
  │  email            ──────────────▶  email                    │
  │  password (crypt) ──────────────▶  password_hash = NULL *   │
  │  ip_addr (TEXT)   ── truncate ──▶  ip_addr (VARCHAR 45)     │
  │  (no column)      ──────────────▶  is_admin = 0             │
  │  (no column)      ──────────────▶  created_at = NOW()       │
  └─────────────────────────────────────────────────────────────┘

  * Old crypt() passwords are not migratable to Argon2.
    Users must reset passwords on first login.
    Migration sets password_hash = NULL.
    Login flow: if password_hash IS NULL → redirect to password reset.

Step 3: Migrate articles:
  articles_info ──▶  articles_info (map bitmask category to category_id)
  articles_text ──▶  articles_text (as-is)

Step 4: Migrate comments:
  comments ──▶  comments (drop nature, to_user_id, chars columns)

Step 5: Seed categories:
  Extract unique category names from bitmask mappings ──▶ categories table
```

---

## 10. Docker Changes

### Updated `phpfpm.Dockerfile`

```dockerfile
FROM php:8.3-fpm

RUN apt-get update && apt-get install -y \
    libzip-dev \
    unzip \
    && docker-php-ext-install pdo pdo_mysql \
    && rm -rf /var/lib/apt/lists/*

COPY --from=composer:latest /usr/bin/composer /usr/bin/composer

WORKDIR /app
```

**What changed:**
- PHP 8.2 → 8.3
- `mysqli` → `pdo pdo_mysql`
- PEAR install commands deleted
- Composer added
- `locate`/`updatedb` removed (debugging tool, not needed)

### Updated `docker-compose.yml` Volume Mounts

```yaml
phpfpm:
    volumes:
        - .:/app                           # entire project (not just web/)
        - ./docker/php/php.ini:/usr/local/etc/php/php.ini

nginx:
    volumes:
        - ./public:/app:ro                 # only public/ is web-accessible
        - ./docker/nginx/default.conf:/opt/bitnami/nginx/conf/server_blocks/swinney.conf
```

---

## 11. Design Decisions (Resolved)

All questions resolved 2026-03-01.

| # | Question | Decision | Notes |
|---|----------|----------|-------|
| 1 | **Visual style** | **Preserve 90s aesthetic** | Table-based HTML, original CSS. The look is the brand. Twig templates reproduce the existing layout, not modernize it. |
| 2 | **Existing data** | **Import 2011 SQL dump** | Articles and comments are the soul of the site. Phinx seed migrates data into new schema. Old `crypt()` passwords → NULL (users reset on first login). |
| 3 | **Admin** | **Full admin panel** | 6 routes, 5 templates. Article CRUD, comment moderation, user list. |
| 4 | **Comments** | **Auth required** | No anonymous comments. Eliminates spam without needing the bozo system. Bozo can return later if anonymous comments are re-enabled. |
| 5 | **HTTPS** | **Self-signed for dev, Let's Encrypt for prod** | `secure: true` on session cookies requires HTTPS. Security headers tested in dev. |
| 6 | **Search** | **MySQL FULLTEXT index** | `ALTER TABLE` + `MATCH() AGAINST()` replaces `LIKE '%term%'`. Better relevance ranking, same effort. |

---

## 12. Implementation Phases

Since the site is dead and unhosted, we don't need incremental keep-it-running phases. But we still want deployable milestones.

```
PHASE A: Skeleton                              PHASE B: Core Features
════════════════════                            ════════════════════════
• Composer + PSR-4 autoloading                  • Article listing (home)
• Slim 4 app bootstrap                          • Article view + comments
• PHP-DI container                              • Search
• Twig environment                              • User profile pages
• PDO Database service                          • Roll call
• Session + CSRF middleware
• Docker updates (PHP 8.3, no PEAR)
• Phinx + baseline migration
• layout.twig + 404.twig

Deliverable: "Hello World" on                  Deliverable: Public site
localhost with auth working                    is fully browsable
           │                                              │
           ▼                                              ▼
PHASE C: Authenticated Features                PHASE D: Admin + Hardening
════════════════════════════════                ═══════════════════════════
• Article submission form                       • Admin dashboard
• Comment posting (auth required)               • Article CRUD (edit, status)
• Password reset flow                           • Comment moderation
  (for migrated users)                          • User list
                                                • Rate limiting middleware
                                                • Security headers (Nginx)
                                                • Data migration from 2011 dump

Deliverable: Users can register,               Deliverable: MVP complete.
login, write, and comment                      Ready to host.
```

---

*This document is the design source-of-truth for the Swinney.org MVP relaunch. It lives alongside [MODERNIZATION.md](MODERNIZATION.md) which contains the full long-term roadmap.*
