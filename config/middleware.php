<?php

declare(strict_types=1);

use Psr\Http\Message\ResponseInterface as Response;
use Psr\Http\Message\ServerRequestInterface as Request;
use Psr\Http\Server\RequestHandlerInterface as Handler;
use Slim\App;
use Slim\Csrf\Guard;
use Slim\Exception\HttpNotFoundException;
use Slim\Psr7\Factory\ResponseFactory;
use Twig\Environment as TwigEnvironment;

return function (App $app): void {
    // Body parsing (JSON, form data)
    $app->addBodyParsingMiddleware();

    // Routing middleware
    $app->addRoutingMiddleware();

    // CSRF protection — provide explicit array storage (no session dependency at setup time)
    $responseFactory = $app->getResponseFactory();
    $storage = [];
    $csrf = new Guard($responseFactory, 'csrf', $storage);
    $csrf->setPersistentTokenMode(true);
    $app->add($csrf);

    // Make CSRF tokens available to Twig (runs after session + CSRF in the middleware stack)
    $app->add(function (Request $request, Handler $handler) use ($app, $csrf): Response {
        $twig = $app->getContainer()->get(TwigEnvironment::class);
        $twig->addGlobal('csrf', [
            'keys' => [
                'name' => $csrf->getTokenNameKey(),
                'value' => $csrf->getTokenValueKey(),
            ],
            'name' => $csrf->getTokenName(),
            'value' => $csrf->getTokenValue(),
        ]);
        return $handler->handle($request);
    });

    // Session middleware (outermost = runs first in request lifecycle)
    $app->add(function (Request $request, Handler $handler): Response {
        if (session_status() === PHP_SESSION_NONE) {
            session_set_cookie_params([
                'lifetime' => 86400 * 30,
                'path' => '/',
                'domain' => '',
                'secure' => false, // false for dev (HTTP), true for prod (HTTPS)
                'httponly' => true,
                'samesite' => 'Lax',
            ]);
            session_start();
        }
        return $handler->handle($request);
    });

    // Error handling (outermost — catches everything)
    $errorMiddleware = $app->addErrorMiddleware(
        displayErrorDetails: true,
        logErrors: true,
        logErrorDetails: true
    );

    // Custom 404 handler — render 404.twig
    $errorMiddleware->setErrorHandler(
        HttpNotFoundException::class,
        function (Request $request, \Throwable $exception, bool $displayErrorDetails) use ($app): Response {
            $twig = $app->getContainer()->get(TwigEnvironment::class);
            $response = (new ResponseFactory())->createResponse(404);
            $response->getBody()->write($twig->render('404.twig', ['title' => '404 - Page Not Found']));
            return $response;
        }
    );
};
