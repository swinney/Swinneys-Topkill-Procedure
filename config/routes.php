<?php

declare(strict_types=1);

use Psr\Http\Message\ResponseInterface as Response;
use Psr\Http\Message\ServerRequestInterface as Request;
use Slim\App;
use Twig\Environment as TwigEnvironment;

return function (App $app): void {
    $render = function (Request $request, Response $response, string $template, array $data = []) use ($app): Response {
        $twig = $app->getContainer()->get(TwigEnvironment::class);
        $html = $twig->render($template, $data);
        $response->getBody()->write($html);
        return $response;
    };

    // ── Public routes ──

    $app->get('/', function (Request $request, Response $response) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => 'Swinney.org',
        ]);
    });

    $app->get('/article/{id}', function (Request $request, Response $response, array $args) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => 'Article ' . $args['id'],
            'placeholder' => 'Article view — coming soon',
        ]);
    });

    $app->get('/search', function (Request $request, Response $response) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => 'Search',
            'placeholder' => 'Search — coming soon',
        ]);
    });

    $app->get('/user/{username}', function (Request $request, Response $response, array $args) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => $args['username'],
            'placeholder' => 'User profile — coming soon',
        ]);
    });

    $app->get('/rollcall', function (Request $request, Response $response) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => 'Roll Call',
            'placeholder' => 'Roll call — coming soon',
        ]);
    });

    // ── Auth routes ──

    $app->get('/login', function (Request $request, Response $response) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => 'Login',
            'placeholder' => 'Login form — coming soon',
        ]);
    });

    $app->post('/login', function (Request $request, Response $response): Response {
        $response->getBody()->write('Login processing — coming soon');
        return $response;
    });

    $app->get('/register', function (Request $request, Response $response) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => 'Register',
            'placeholder' => 'Registration form — coming soon',
        ]);
    });

    $app->post('/register', function (Request $request, Response $response): Response {
        $response->getBody()->write('Registration processing — coming soon');
        return $response;
    });

    $app->get('/logout', function (Request $request, Response $response): Response {
        $response->getBody()->write('Logout — coming soon');
        return $response;
    });

    // ── Authenticated routes ──

    $app->get('/submit', function (Request $request, Response $response) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => 'Submit Article',
            'placeholder' => 'Article submission — coming soon',
        ]);
    });

    $app->post('/submit', function (Request $request, Response $response): Response {
        $response->getBody()->write('Article processing — coming soon');
        return $response;
    });

    $app->post('/comment', function (Request $request, Response $response): Response {
        $response->getBody()->write('Comment processing — coming soon');
        return $response;
    });

    // ── Admin routes ──

    $app->get('/admin', function (Request $request, Response $response) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => 'Admin Dashboard',
            'placeholder' => 'Admin dashboard — coming soon',
        ]);
    });

    $app->get('/admin/articles', function (Request $request, Response $response) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => 'Admin: Articles',
            'placeholder' => 'Article management — coming soon',
        ]);
    });

    $app->get('/admin/articles/{id}/edit', function (Request $request, Response $response, array $args) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => 'Edit Article ' . $args['id'],
            'placeholder' => 'Article editor — coming soon',
        ]);
    });

    $app->post('/admin/articles/{id}', function (Request $request, Response $response): Response {
        $response->getBody()->write('Article save — coming soon');
        return $response;
    });

    $app->post('/admin/articles/{id}/status', function (Request $request, Response $response): Response {
        $response->getBody()->write('Status change — coming soon');
        return $response;
    });

    $app->get('/admin/comments', function (Request $request, Response $response) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => 'Admin: Comments',
            'placeholder' => 'Comment moderation — coming soon',
        ]);
    });

    $app->post('/admin/comments/{id}', function (Request $request, Response $response): Response {
        $response->getBody()->write('Comment moderation — coming soon');
        return $response;
    });

    $app->get('/admin/users', function (Request $request, Response $response) use ($render): Response {
        return $render($request, $response, 'home.twig', [
            'title' => 'Admin: Users',
            'placeholder' => 'User management — coming soon',
        ]);
    });
};
