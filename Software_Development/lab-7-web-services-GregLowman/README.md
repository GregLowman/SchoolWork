# Web Services — Authentication and Discovery

A full-stack Node.js application with user authentication and a content discovery feature, using Handlebars templates.

## Overview

- Login and registration with session-based authentication
- Discovery page served from a PostgreSQL-backed API
- Handlebars (`.hbs`) templates for server-side rendering
- Docker Compose for local development

## Usage

```bash
docker-compose up --build
```

Navigate to `localhost:3000` in your browser.

## Structure

```
index.js          — Express routes and middleware
views/            — Handlebars page templates
views/layouts/    — base layout
views/partials/   — reusable partials
init_data/        — database schema and seed SQL
```
