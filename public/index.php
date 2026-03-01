<?php

declare(strict_types=1);

require __DIR__ . '/../vendor/autoload.php';

use DI\ContainerBuilder;
use Slim\Factory\AppFactory;

// Load settings
$settings = require __DIR__ . '/../config/settings.php';

// Build DI container
$containerBuilder = new ContainerBuilder();
$containerDefinitions = require __DIR__ . '/../config/container.php';
$containerDefinitions($containerBuilder, $settings);
$container = $containerBuilder->build();

// Create Slim app with PHP-DI container
AppFactory::setContainer($container);
$app = AppFactory::create();

// Register middleware
$middleware = require __DIR__ . '/../config/middleware.php';
$middleware($app);

// Register routes
$routes = require __DIR__ . '/../config/routes.php';
$routes($app);

// Run
$app->run();
