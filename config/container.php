<?php

declare(strict_types=1);

use DI\ContainerBuilder;
use Psr\Container\ContainerInterface;
use Swinsite\Service\Database;
use Twig\Environment as TwigEnvironment;
use Twig\Loader\FilesystemLoader;

return function (ContainerBuilder $containerBuilder, array $settings): void {
    $containerBuilder->addDefinitions([
        'settings' => $settings,

        PDO::class => function (ContainerInterface $c): PDO {
            $db = $c->get('settings')['db'];
            $dsn = sprintf(
                'mysql:host=%s;port=%d;dbname=%s;charset=utf8mb4',
                $db['host'],
                $db['port'],
                $db['name']
            );
            $pdo = new PDO($dsn, $db['user'], $db['password'], [
                PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
                PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
                PDO::ATTR_EMULATE_PREPARES => false,
            ]);
            return $pdo;
        },

        Database::class => function (ContainerInterface $c): Database {
            return new Database($c->get(PDO::class));
        },

        TwigEnvironment::class => function (ContainerInterface $c): TwigEnvironment {
            $settings = $c->get('settings')['twig'];
            $loader = new FilesystemLoader($settings['path']);
            $twig = new TwigEnvironment($loader, [
                'cache' => $settings['cache'],
                'auto_reload' => true,
            ]);
            return $twig;
        },
    ]);
};
