# Docker Containers: Dev-Optimized Spec

> **Context:** Dead-on-arrival relaunch. No production hosting yet. These containers exist purely to support rapid local development until a hosting decision is made. Production hardening is a separate spec.

---

## 1. Current State vs. Target

```
CURRENT SETUP                              TARGET SETUP
═══════════════                            ═══════════════

┌────────────────────┐                     ┌────────────────────┐
│    so_nginx        │                     │    so_nginx        │
│ bitnami/nginx:latest│                    │ nginx:1.27-alpine  │
│ Serves ./web as /app│                    │ Serves ./public    │
│ Read-only mount    │                     │ Live reload ready  │
│ No gzip            │                     │ gzip on            │
│ No security headers│                     │ Security headers   │
└────────┬───────────┘                     └────────┬───────────┘
         │ :9000                                    │ :9000
┌────────▼───────────┐                     ┌────────▼───────────┐
│    so_phpfmp       │                     │    so_phpfpm       │
│ php:8.2-fpm        │                     │ php:8.3-fpm        │
│ mysqli only        │                     │ PDO + Xdebug       │
│ PEAR extensions    │                     │ Composer built-in  │
│ opcache 60s stale  │                     │ opcache OFF in dev │
│ No Composer        │                     │ Error display ON   │
│ No Xdebug          │                     │ File watcher ready │
│ 1942-line php.ini  │                     │ 30-line dev php.ini│
└────────────────────┘                     └────────────────────┘

┌────────────────────┐                     ┌────────────────────┐
│    so_mysql        │                     │    so_mysql        │
│ mysql:latest       │                     │ mysql:8.4          │
│ No health check    │                     │ Health check       │
│ Manual SQL import  │                     │ Auto-init via Phinx│
│ Data in ./data/db  │                     │ Named volume       │
└────────────────────┘                     │ Perf-tuned for dev │
                                           └────────────────────┘

                                           ┌────────────────────┐
                                           │  NEW: so_mailpit   │
                                           │ Email capture      │
                                           │ Web UI :8025       │
                                           │ SMTP :1025         │
                                           └────────────────────┘
```

---

## 2. Service Architecture

```
                    HOST MACHINE
    ┌──────────────────────────────────────────────────┐
    │                                                  │
    │   localhost:80 ──────────┐                       │
    │   localhost:443 ─────────┤                       │
    │   localhost:3306 ────────┼──── Direct DB access  │
    │   localhost:8025 ────────┼──── Mailpit Web UI    │
    │   localhost:9003 ────────┼──── Xdebug (IDE)      │
    │                          │                       │
    └──────────────────────────┼───────────────────────┘
                               │
           ┌───────────────────▼───────────────────┐
           │          Docker Network: swinney      │
           │                                       │
           │  ┌─────────┐  ┌─────────┐            │
           │  │  nginx   │  │  phpfpm │            │
           │  │  :80/:443│──│  :9000  │            │
           │  └─────────┘  └────┬────┘            │
           │                    │                   │
           │          ┌─────────┼─────────┐        │
           │          │         │         │        │
           │     ┌────▼───┐ ┌──▼────┐ ┌──▼────┐  │
           │     │ mysql  │ │mailpit│ │(redis?)│  │
           │     │ :3306  │ │ :1025 │ │ :6379  │  │
           │     │        │ │ :8025 │ │        │  │
           │     └────────┘ └───────┘ └────────┘  │
           │                                       │
           └───────────────────────────────────────┘
```

### Port Map

| Port | Service | Purpose |
|------|---------|---------|
| 80 | Nginx | HTTP (site) |
| 443 | Nginx | HTTPS (self-signed for dev) |
| 3306 | MySQL | Direct DB access from host tools (TablePlus, DBeaver, CLI) |
| 8025 | Mailpit | Email capture web UI — see all "sent" emails |
| 1025 | Mailpit | SMTP — PHP `mail()` and registration emails land here |
| 9003 | Xdebug | Step debugger (VS Code / PhpStorm connect here) |

---

## 3. PHP-FPM Container (`so_phpfpm`)

### Dockerfile: `docker/php/Dockerfile`

```dockerfile
FROM php:8.3-fpm-alpine

# System deps
RUN apk add --no-cache \
    linux-headers \
    $PHPIZE_DEPS \
    icu-dev \
    libzip-dev

# PHP extensions
RUN docker-php-ext-install \
    pdo_mysql \
    intl \
    zip \
    opcache

# Xdebug (dev only — controlled by env var)
RUN pecl install xdebug-3.3.2 \
    && docker-php-ext-enable xdebug

# Composer (from official image)
COPY --from=composer:2 /usr/bin/composer /usr/bin/composer

WORKDIR /app
```

**Key decisions:**

| Decision | Rationale |
|----------|-----------|
| **Alpine base** | 50MB vs 400MB. Faster pull, smaller disk footprint. |
| **`pdo_mysql`** not `mysqli` | PDO is the target stack. No PEAR, no mysqli. |
| **Xdebug installed but env-controlled** | `XDEBUG_MODE=off` by default. Set to `debug` when needed. No rebuild required. |
| **Composer baked in** | Run `docker compose exec phpfpm composer install` without entering the container. |
| **`intl` extension** | For proper UTF-8 handling, date formatting. Costs nothing. |
| **`zip` extension** | Required by Composer for package installation. |
| **No PEAR** | Dead. Gone. Eliminated. |

### PHP Configuration: `docker/php/dev.ini`

Replaces the 1942-line stock `php.ini` with a focused dev override:

```ini
[PHP]
; ── Error visibility (show everything in dev) ──
display_errors = On
display_startup_errors = On
error_reporting = E_ALL
log_errors = On
error_log = /proc/self/fd/2

; ── Performance (dev = no caching) ──
opcache.enable = 0
opcache.enable_cli = 0
realpath_cache_size = 0
realpath_cache_ttl = 0

; ── Uploads ──
upload_max_filesize = 10M
post_max_size = 12M

; ── Session ──
session.cookie_httponly = 1
session.cookie_samesite = Lax
session.use_strict_mode = 1

; ── Timezone ──
date.timezone = UTC

; ── Xdebug (activated via XDEBUG_MODE env var) ──
[xdebug]
xdebug.client_host = host.docker.internal
xdebug.client_port = 9003
xdebug.start_with_request = trigger
xdebug.idekey = VSCODE
```

**What this achieves:**

```
BEFORE (stock php.ini)                 AFTER (dev.ini)
══════════════════════                 ═══════════════

1942 lines                             30 lines
opcache revalidate = 60s               opcache OFF (instant changes)
errors partially visible               ALL errors shown
no xdebug config                       xdebug ready (env-triggered)
no session security                    httponly + samesite
error_log = ???                        error_log = stderr (docker logs)
```

### Xdebug Activation

Xdebug is installed but **off by default** (zero performance hit). Activate it per-session:

```bash
# Turn on step debugging
XDEBUG_MODE=debug docker compose up phpfpm

# Turn on profiling
XDEBUG_MODE=profile docker compose up phpfpm

# Turn on coverage (for PHPUnit)
XDEBUG_MODE=coverage docker compose exec phpfpm vendor/bin/phpunit

# Normal development (default — xdebug loaded but inactive)
XDEBUG_MODE=off docker compose up
```

Or override in `docker-compose.override.yml` (see Section 7).

---

## 4. Nginx Container (`so_nginx`)

### Configuration: `docker/nginx/default.conf`

```nginx
server {
    listen 80;
    server_name localhost;
    root /app/public;
    index index.php;

    # ── Dev: disable caching ──
    sendfile off;
    expires off;
    etag off;
    add_header Cache-Control "no-store, no-cache";

    # ── Security headers (even in dev — test what prod will do) ──
    add_header X-Content-Type-Options "nosniff" always;
    add_header X-Frame-Options "DENY" always;
    add_header Referrer-Policy "strict-origin-when-cross-origin" always;

    # ── Gzip ──
    gzip on;
    gzip_types text/css application/javascript text/plain application/json;

    # ── Front controller: everything routes through index.php ──
    location / {
        try_files $uri $uri/ /index.php$is_args$args;
    }

    # ── PHP handler ──
    location ~ \.php$ {
        fastcgi_pass phpfpm:9000;
        fastcgi_index index.php;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        include fastcgi_params;

        # ── Dev: no buffering (see errors immediately) ──
        fastcgi_buffering off;
    }

    # ── Static assets ──
    location ~* \.(css|js|ico|gif|jpe?g|png|svg|woff2?)$ {
        expires 1h;
        add_header Cache-Control "public";
        access_log off;
    }

    # ── Block dotfiles ──
    location ~ /\. {
        deny all;
        access_log off;
        log_not_found off;
    }
}
```

**Key changes from current:**

| Current | New | Why |
|---------|-----|-----|
| `bitnami/nginx:latest` | `nginx:1.27-alpine` | Standard image. Pinned version. Alpine = smaller. |
| `root /app` (entire web/) | `root /app/public` | Only `index.php` is web-accessible. Source code above webroot. |
| `try_files $uri $uri/index.php` | `try_files $uri $uri/ /index.php$is_args$args` | Slim 4 front controller routing. All paths go through `index.php`. |
| No security headers | X-Content-Type-Options, X-Frame-Options, Referrer-Policy | Test security behavior in dev so prod doesn't surprise you. |
| No gzip | gzip on | Faster page loads even locally. |
| No dotfile blocking | `deny all` on `/\.` | Prevents `.env`, `.git/` from being served. |
| `fastcgi_buffering` on | `fastcgi_buffering off` | See errors and output immediately. No buffered surprises. |

---

## 5. MySQL Container (`so_mysql`)

```yaml
mysql:
    image: mysql:8.4
    container_name: so_mysql
    hostname: so_mysql
    restart: unless-stopped
    environment:
        MYSQL_DATABASE: ${DB_NAME}
        MYSQL_ROOT_PASSWORD: ${DB_ROOT_PASSWORD}
        MYSQL_USER: ${DB_USER}
        MYSQL_PASSWORD: ${DB_PASSWORD}
    ports:
        - "${DB_PORT:-3306}:3306"
    volumes:
        - mysql_data:/var/lib/mysql
        - ./docker/mysql/dev.cnf:/etc/mysql/conf.d/dev.cnf:ro
    healthcheck:
        test: ["CMD", "mysqladmin", "ping", "-h", "localhost", "-u", "root", "-p${DB_ROOT_PASSWORD}"]
        interval: 5s
        timeout: 3s
        retries: 10
        start_period: 30s
```

### MySQL Dev Config: `docker/mysql/dev.cnf`

```ini
[mysqld]
# ── Dev performance (trade durability for speed) ──
innodb_flush_log_at_trx_commit = 0
innodb_flush_method = O_DIRECT
sync_binlog = 0
innodb_doublewrite = 0

# ── Logging (see all queries during development) ──
general_log = 1
general_log_file = /var/lib/mysql/general.log
slow_query_log = 1
slow_query_log_file = /var/lib/mysql/slow.log
long_query_time = 1

# ── Charset ──
character-set-server = utf8mb4
collation-server = utf8mb4_unicode_ci

# ── Disable binary log (no replication needed) ──
skip-log-bin
```

**Key decisions:**

| Decision | Rationale |
|----------|-----------|
| **`mysql:8.4`** (pinned) | No more `mysql:latest` roulette. Reproducible builds. |
| **Named volume** (`mysql_data`) | Not `./data/db/mysql` bind mount. Faster I/O on macOS (bind mounts are notoriously slow). Named volumes use the Linux VM's native filesystem. |
| **Health check** | `docker compose up` now waits for MySQL to actually accept connections before PHP tries to connect. No more "connection refused" race conditions. |
| **`innodb_flush_log_at_trx_commit = 0`** | Trades crash durability for write speed. If Docker dies, who cares — it's dev data. Gives a meaningful speedup on schema migrations and seed imports. |
| **`general_log = 1`** | See every SQL query during development. Tail with `docker compose exec mysql tail -f /var/lib/mysql/general.log`. |
| **`skip-log-bin`** | No binary log. Saves disk and CPU. Not replicating. |
| **Removed `./db/swinney.db.2011.02.16.sql` mount** | Data initialization moves to Phinx migrations + seeds. No raw SQL dump mount. |

---

## 6. Mailpit Container (NEW)

```yaml
mailpit:
    image: axllent/mailpit:latest
    container_name: so_mailpit
    ports:
        - "8025:8025"    # Web UI
        - "1025:1025"    # SMTP
```

**Why:** The original app sends emails on article submission and registration (`mail()` to `swinney@swinney.org`). Without Mailpit, those calls either fail silently or need a real SMTP server. Mailpit captures all outbound email and shows it in a web UI at `localhost:8025`.

PHP config in `.env`:

```
MAIL_HOST=mailpit
MAIL_PORT=1025
```

---

## 7. Full `docker-compose.yml`

```yaml
networks:
    swinney:
        driver: bridge

volumes:
    mysql_data:

services:
    nginx:
        image: nginx:1.27-alpine
        container_name: so_nginx
        depends_on:
            phpfpm:
                condition: service_started
        networks:
            - swinney
        ports:
            - "80:80"
        volumes:
            - .:/app:ro
            - ./docker/nginx/default.conf:/etc/nginx/conf.d/default.conf:ro

    phpfpm:
        build:
            context: .
            dockerfile: docker/php/Dockerfile
        container_name: so_phpfpm
        depends_on:
            mysql:
                condition: service_healthy
        networks:
            - swinney
        environment:
            XDEBUG_MODE: "${XDEBUG_MODE:-off}"
        volumes:
            - .:/app
            - ./docker/php/dev.ini:/usr/local/etc/php/conf.d/zz-dev.ini:ro
        working_dir: /app

    mysql:
        image: mysql:8.4
        container_name: so_mysql
        restart: unless-stopped
        networks:
            - swinney
        env_file: .env
        environment:
            MYSQL_DATABASE: ${DB_NAME}
            MYSQL_ROOT_PASSWORD: ${DB_ROOT_PASSWORD}
            MYSQL_USER: ${DB_USER}
            MYSQL_PASSWORD: ${DB_PASSWORD}
        ports:
            - "${DB_PORT:-3306}:3306"
        volumes:
            - mysql_data:/var/lib/mysql
            - ./docker/mysql/dev.cnf:/etc/mysql/conf.d/dev.cnf:ro
        healthcheck:
            test: ["CMD", "mysqladmin", "ping", "-h", "localhost", "-u", "root", "-p${DB_ROOT_PASSWORD}"]
            interval: 5s
            timeout: 3s
            retries: 10
            start_period: 30s

    mailpit:
        image: axllent/mailpit:latest
        container_name: so_mailpit
        networks:
            - swinney
        ports:
            - "8025:8025"
            - "1025:1025"
```

### Override File: `docker-compose.override.yml`

For personal dev preferences that shouldn't be committed:

```yaml
# Example: enable Xdebug by default
services:
    phpfpm:
        environment:
            XDEBUG_MODE: debug
```

This file is auto-loaded by Docker Compose and should be in `.gitignore`.

---

## 8. Environment File (`.env`)

```bash
# ── App ──
APP_ENV=development
APP_URL=http://localhost

# ── Database ──
DB_NAME=swinney
DB_HOST=so_mysql
DB_PORT=3306
DB_USER=swinney_app
DB_PASSWORD=hamsandwich
DB_ROOT_PASSWORD=bananas

# ── Mail ──
MAIL_HOST=mailpit
MAIL_PORT=1025

# ── Debug ──
XDEBUG_MODE=off
```

**Changes from current `.env`:**

| Current | New | Why |
|---------|-----|-----|
| `MYSQL_*` prefix | `DB_*` prefix | Matches PHP conventions (phpdotenv). MySQL env vars are set separately in compose. |
| `MYSQL_HOST=localhost` | `DB_HOST=so_mysql` | Hostname inside Docker network. `localhost` is the host machine, not the container. |
| `MYSQL_USER=admin` | `DB_USER=swinney_app` | Descriptive. Not `admin`, not `root` for app access. |
| No `APP_ENV` | `APP_ENV=development` | Controls error display, opcache, debug behavior. |
| No `MAIL_*` | `MAIL_HOST=mailpit` | Mailpit integration. |
| No `XDEBUG_MODE` | `XDEBUG_MODE=off` | Env-controlled debugger. |

---

## 9. Developer Shortcuts: `Makefile`

```makefile
.PHONY: up down build shell db migrate seed logs fresh xdebug test

# ── Lifecycle ──
up:                ## Start all containers
	docker compose up -d

down:              ## Stop all containers
	docker compose down

build:             ## Rebuild PHP container (after Dockerfile changes)
	docker compose up -d --build phpfpm

fresh:             ## Nuclear option: rebuild everything from scratch
	docker compose down -v
	docker compose up -d --build
	$(MAKE) install
	$(MAKE) migrate
	$(MAKE) seed

# ── PHP / Composer ──
shell:             ## Open a shell in PHP container
	docker compose exec phpfpm sh

install:           ## Run composer install
	docker compose exec phpfpm composer install

# ── Database ──
db:                ## Open MySQL CLI
	docker compose exec mysql mysql -u root -p$(DB_ROOT_PASSWORD) $(DB_NAME)

migrate:           ## Run Phinx migrations
	docker compose exec phpfpm vendor/bin/phinx migrate

seed:              ## Run Phinx seed data
	docker compose exec phpfpm vendor/bin/phinx seed:run

rollback:          ## Rollback last migration
	docker compose exec phpfpm vendor/bin/phinx rollback

# ── Debug ──
logs:              ## Tail all container logs
	docker compose logs -f

logs-php:          ## Tail PHP error log only
	docker compose logs -f phpfpm

logs-sql:          ## Tail MySQL general query log
	docker compose exec mysql tail -f /var/lib/mysql/general.log

xdebug:            ## Restart PHP with Xdebug enabled
	XDEBUG_MODE=debug docker compose up -d phpfpm

# ── Test ──
test:              ## Run PHPUnit
	docker compose exec phpfpm vendor/bin/phpunit

test-coverage:     ## Run PHPUnit with coverage
	docker compose exec -e XDEBUG_MODE=coverage phpfpm vendor/bin/phpunit --coverage-html coverage/
```

**Workflow examples:**

```bash
# First time setup
make build && make install && make migrate && make seed

# Or just:
make fresh

# Daily development
make up                # start containers
make logs-php          # tail errors in a split terminal
# edit code, refresh browser, see changes instantly

# Need to debug a tricky bug
make xdebug            # restarts PHP with step debugger
# set breakpoint in VS Code, refresh browser, step through

# Check what SQL is running
make logs-sql           # see every query MySQL receives

# Wrote a new migration
make migrate            # apply it

# Run tests
make test

# Done for the day
make down
```

---

## 10. Dev Cycle: Before & After

```
BEFORE                                    AFTER
══════                                    ═════

Edit PHP file                             Edit PHP file
  ↓                                         ↓
Wait 0-60 seconds (opcache)               Refresh browser (instant)
  ↓                                         ↓
See blank page (error_display=???)        See full error with stack trace
  ↓                                         ↓
Add var_dump() to debug                   Set breakpoint in IDE
  ↓                                         ↓
Rebuild container to try something        Change .env, restart container
  ↓                                         ↓
"Connection refused" from MySQL           Health check ensures MySQL
(race condition on startup)               is ready before PHP starts
  ↓                                         ↓
SSH into container to run commands        `make shell`, `make migrate`,
                                          `make db` from host
  ↓                                         ↓
Wonder if emails were sent                Check localhost:8025 (Mailpit)
  ↓                                         ↓
Guess what SQL queries are running        `make logs-sql` — see every query
```

---

## 11. File Layout Summary

```
docker/
├── nginx/
│   └── default.conf         ◀── Slim 4 front controller routing
├── php/
│   ├── Dockerfile           ◀── PHP 8.3 + PDO + Xdebug + Composer
│   └── dev.ini              ◀── 30-line dev PHP config
└── mysql/
    └── dev.cnf              ◀── Fast-writes, query logging, utf8mb4

docker-compose.yml           ◀── 4 services: nginx, phpfpm, mysql, mailpit
docker-compose.override.yml  ◀── Personal overrides (.gitignore'd)
.env                         ◀── All credentials and config
.env.example                 ◀── Template (committed, no secrets)
Makefile                     ◀── Developer shortcuts
```

### What's Deleted

| File/Dir | Reason |
|----------|--------|
| `phpfpm.Dockerfile` | Replaced by `docker/php/Dockerfile` |
| `etc/php/php.ini` (1942 lines) | Replaced by `docker/php/dev.ini` (30 lines) |
| `etc/nginx/default.conf` | Replaced by `docker/nginx/default.conf` |
| `etc/nginx/fastcgi_params` | Standard `fastcgi_params` ships with `nginx:alpine` |
| `etc/phpfpm/` | Not needed — defaults are fine |
| `pear/` | Dead. Replaced by Composer. |
| `swinlib/` | Dead. Replaced by Composer. |
| `data/db/mysql/` | Replaced by named Docker volume. |
| `go-pear.phar` | PEAR is gone. |
| `containers` (submodule) | Laradock reference, unused. |

---

## 12. Container Startup Sequence

```
docker compose up -d
         │
         ▼
    ┌─────────┐
    │  mysql   │  Starts first (no deps)
    │          │  Health check: mysqladmin ping
    │  ·····   │  Retries every 5s for up to 50s
    │  HEALTHY │
    └────┬─────┘
         │
         ▼
    ┌─────────┐
    │  phpfpm  │  Waits for mysql: service_healthy
    │          │  Mounts project root as /app
    │  RUNNING │  Composer autoloader ready
    └────┬─────┘
         │
         ▼
    ┌─────────┐    ┌─────────┐
    │  nginx   │    │ mailpit │  Start independently
    │          │    │         │
    │  :80     │    │  :8025  │
    └──────────┘    └─────────┘

    Total cold start: ~15-20 seconds
    Subsequent starts: ~3-5 seconds (volume cached)
```

---

*This spec covers the development environment only. Production container hardening (multi-stage builds, opcache on, no Xdebug, read-only filesystem, non-root user, health endpoints) is a separate concern for when hosting decisions are made.*
