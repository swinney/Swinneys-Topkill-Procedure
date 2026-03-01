<?php

declare(strict_types=1);

use Dotenv\Dotenv;

// Load .env from project root
$dotenv = Dotenv::createImmutable(dirname(__DIR__));
$dotenv->load();

return [
    'app' => [
        'env' => $_ENV['APP_ENV'] ?? 'development',
        'url' => $_ENV['APP_URL'] ?? 'http://localhost',
    ],
    'db' => [
        'host' => $_ENV['DB_HOST'] ?? 'so_mysql',
        'port' => (int) ($_ENV['DB_PORT'] ?? 3306),
        'name' => $_ENV['DB_NAME'] ?? 'swinney',
        'user' => $_ENV['DB_USER'] ?? 'swinney_app',
        'password' => $_ENV['DB_PASSWORD'] ?? '',
    ],
    'twig' => [
        'path' => dirname(__DIR__) . '/templates',
        'cache' => false, // No cache in development
    ],
    'mail' => [
        'host' => $_ENV['MAIL_HOST'] ?? 'mailpit',
        'port' => (int) ($_ENV['MAIL_PORT'] ?? 1025),
    ],
];
