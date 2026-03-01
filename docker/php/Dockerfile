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
RUN pecl install xdebug \
    && docker-php-ext-enable xdebug

# Composer (from official image)
COPY --from=composer:2 /usr/bin/composer /usr/bin/composer

WORKDIR /app
