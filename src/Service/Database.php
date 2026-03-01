<?php

declare(strict_types=1);

namespace Swinsite\Service;

use PDO;
use PDOStatement;

class Database
{
    public function __construct(
        private readonly PDO $pdo,
    ) {}

    /**
     * Execute a query with prepared statement parameters.
     */
    public function query(string $sql, array $params = []): PDOStatement
    {
        $stmt = $this->pdo->prepare($sql);
        $stmt->execute($params);
        return $stmt;
    }

    /**
     * Fetch a single row as an associative array.
     */
    public function getRow(string $sql, array $params = []): ?array
    {
        $stmt = $this->query($sql, $params);
        $row = $stmt->fetch();
        return $row !== false ? $row : null;
    }

    /**
     * Fetch all rows as an array of associative arrays.
     */
    public function getAll(string $sql, array $params = []): array
    {
        $stmt = $this->query($sql, $params);
        return $stmt->fetchAll();
    }
}
