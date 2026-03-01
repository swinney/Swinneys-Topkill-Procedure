.PHONY: up down build shell db migrate seed rollback logs logs-php logs-sql fresh xdebug test test-coverage install

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
	docker compose exec mysql mysql -u root -p$${DB_ROOT_PASSWORD:-bananas} $${DB_NAME:-swinney}

migrate:           ## Run Phinx migrations
	docker compose exec phpfpm vendor/bin/phinx migrate -c db/phinx.php

seed:              ## Run Phinx seed data
	docker compose exec phpfpm vendor/bin/phinx seed:run -c db/phinx.php || true

rollback:          ## Rollback last migration
	docker compose exec phpfpm vendor/bin/phinx rollback -c db/phinx.php

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
