# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is "Swinney's Topkill Procedure" - a legacy PHP web application (swinney.org) that combines a personal journal/blog system with user authentication and article management. The application is containerized using Docker and deployed on AWS ECS.

## Architecture

### Core Components

- **so_app/**: Main PHP application container
  - `src/`: PHP application source code (journals, articles, user management)
  - `lib/Swinsite/`: Custom PHP object-oriented framework with persistence layer
  - `etc/`: Configuration files for nginx, PHP-FPM, and supervisor
  - Dockerfile builds multi-service container (nginx + PHP-FPM + supervisor)

- **so_mysql/**: MySQL database container
  - `src/data.sql`: Database initialization script
  - Provides user accounts, articles, comments, and session storage

- **terraform/**: Infrastructure as Code
  - AWS ECS deployment configuration
  - VPC, subnets, load balancers, RDS, and ECR setup
  - Environment-specific workspaces (dev, staging, prod)

### Application Structure

The PHP application (`so_app/src/`) follows a legacy pattern:
- `journals/`: Core application logic (articles, comments, user management)
- `index.php`: Main entry point with session handling
- `global.php`: Session management and configuration loading
- Custom ORM in `lib/Swinsite/Persistent/` using PEAR DB

## Development Commands

### Local Development
```bash
# Build local container
cd so_app && ./buildx-local.sh

# Run development environment
docker-compose up

# Build and push to ECR
cd so_app && ./buildx.sh
```

### Infrastructure Management
```bash
# Deploy infrastructure
cd terraform
terraform workspace select dev
terraform plan
terraform apply

# AWS ECS access
aws ecs execute-command --cluster dev-ecs-cluster --task [TASK_ID] --container so-app --interactive --command "/bin/bash"
```

### Database Operations
- MySQL initialization handled by `so_mysql/src/data.sql`
- Database updates require changes to `mkdb.sql` and conversion scripts
- Environment variables in `.env` configure database connections

## Key Technical Details

### Container Architecture
- Base image: Custom `so-base` with PHP 8.4, nginx, and PEAR libraries
- Multi-service container managed by supervisor
- Volume mounting for development (`/app` volume in local Dockerfile)
- Environment-specific configuration via `.env` files

### PHP Framework
- Custom ORM using PEAR DB with object persistence
- Session-based authentication system
- Template-based rendering with includes
- Legacy code patterns (circa 2000s) with modern containerization

### AWS Deployment
- ECS Fargate containers
- ECR for container registry
- Multi-environment setup with Terraform workspaces
- Database credentials managed via AWS Secrets Manager

## Development Notes

- The application uses legacy PHP patterns and should be maintained in that style
- Database changes require both schema updates and conversion scripts
- Container builds use multi-platform support (linux/amd64)
- Environment configuration is critical for proper database connectivity
- Session management is handled globally in `journals/global.php`

## File Structure Context

- `/data/`: MySQL data persistence
- `/etc/`: Service configuration (nginx, PHP-FPM)
- `/pear/`: PEAR library dependencies
- `/swinlib/`: Additional PEAR libraries
- `/sessionmanager-bundle/`: AWS Session Manager tools