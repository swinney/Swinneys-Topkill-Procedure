<?php

declare(strict_types=1);

use Phinx\Migration\AbstractMigration;

final class CreateMvpSchema extends AbstractMigration
{
    public function up(): void
    {
        // 1. user
        $this->table('user', ['id' => 'user_id', 'engine' => 'InnoDB', 'collation' => 'utf8mb4_unicode_ci'])
            ->addColumn('username', 'string', ['limit' => 30, 'null' => false])
            ->addColumn('email', 'string', ['limit' => 100, 'null' => true])
            ->addColumn('password_hash', 'string', ['limit' => 255, 'null' => true])
            ->addColumn('ip_addr', 'string', ['limit' => 45, 'null' => true])
            ->addColumn('is_admin', 'boolean', ['default' => false, 'null' => false])
            ->addColumn('created_at', 'timestamp', ['default' => 'CURRENT_TIMESTAMP', 'null' => false])
            ->addIndex(['username'], ['unique' => true, 'name' => 'idx_user_username'])
            ->create();

        // 2. categories
        $this->table('categories', ['id' => 'cat_id', 'engine' => 'InnoDB', 'collation' => 'utf8mb4_unicode_ci'])
            ->addColumn('name', 'string', ['limit' => 40, 'null' => false])
            ->create();

        // 3. articles_info
        $this->table('articles_info', ['id' => 'article_id', 'engine' => 'InnoDB', 'collation' => 'utf8mb4_unicode_ci'])
            ->addColumn('user_id', 'integer', ['signed' => false, 'null' => false])
            ->addColumn('category_id', 'integer', ['signed' => false, 'null' => true])
            ->addColumn('title', 'string', ['limit' => 255, 'null' => true])
            ->addColumn('blurb', 'text', ['null' => true])
            ->addColumn('status', 'integer', ['limit' => \Phinx\Db\Adapter\MysqlAdapter::INT_TINY, 'default' => 0, 'null' => false])
            ->addColumn('keywords', 'string', ['limit' => 255, 'null' => true])
            ->addColumn('num_comments', 'integer', ['default' => 0, 'null' => false])
            ->addColumn('num_hits', 'integer', ['default' => 0, 'null' => false])
            ->addColumn('ip_addr', 'string', ['limit' => 45, 'null' => true])
            ->addColumn('created_at', 'timestamp', ['default' => 'CURRENT_TIMESTAMP', 'null' => false])
            ->addForeignKey('user_id', 'user', 'user_id', ['delete' => 'CASCADE', 'update' => 'CASCADE'])
            ->addForeignKey('category_id', 'categories', 'cat_id', ['delete' => 'SET_NULL', 'update' => 'CASCADE'])
            ->addIndex(['user_id'], ['name' => 'idx_articles_user_id'])
            ->addIndex(['status'], ['name' => 'idx_articles_status'])
            ->addIndex(['created_at'], ['name' => 'idx_articles_created_at'])
            ->create();

        // FULLTEXT index on title + keywords
        $this->execute('ALTER TABLE articles_info ADD FULLTEXT INDEX ft_articles_title_keywords (title, keywords)');

        // 4. articles_text
        $this->table('articles_text', ['id' => false, 'primary_key' => ['article_id'], 'engine' => 'InnoDB', 'collation' => 'utf8mb4_unicode_ci'])
            ->addColumn('article_id', 'integer', ['signed' => false, 'null' => false])
            ->addColumn('text', 'text', ['limit' => \Phinx\Db\Adapter\MysqlAdapter::TEXT_MEDIUM, 'null' => true])
            ->addForeignKey('article_id', 'articles_info', 'article_id', ['delete' => 'CASCADE', 'update' => 'CASCADE'])
            ->create();

        // FULLTEXT index on text
        $this->execute('ALTER TABLE articles_text ADD FULLTEXT INDEX ft_articles_text (text)');

        // 5. comments
        $this->table('comments', ['id' => 'comment_id', 'engine' => 'InnoDB', 'collation' => 'utf8mb4_unicode_ci'])
            ->addColumn('article_id', 'integer', ['signed' => false, 'null' => false])
            ->addColumn('user_id', 'integer', ['signed' => false, 'null' => false])
            ->addColumn('comment', 'text', ['null' => true])
            ->addColumn('status', 'integer', ['limit' => \Phinx\Db\Adapter\MysqlAdapter::INT_TINY, 'default' => 1, 'null' => false])
            ->addColumn('ip_addr', 'string', ['limit' => 45, 'null' => true])
            ->addColumn('created_at', 'timestamp', ['default' => 'CURRENT_TIMESTAMP', 'null' => false])
            ->addForeignKey('article_id', 'articles_info', 'article_id', ['delete' => 'CASCADE', 'update' => 'CASCADE'])
            ->addForeignKey('user_id', 'user', 'user_id', ['delete' => 'CASCADE', 'update' => 'CASCADE'])
            ->addIndex(['article_id'], ['name' => 'idx_comments_article_id'])
            ->addIndex(['user_id'], ['name' => 'idx_comments_user_id'])
            ->create();
    }

    public function down(): void
    {
        // Drop in reverse dependency order
        $this->table('comments')->drop()->save();
        $this->table('articles_text')->drop()->save();
        $this->table('articles_info')->drop()->save();
        $this->table('categories')->drop()->save();
        $this->table('user')->drop()->save();
    }
}
