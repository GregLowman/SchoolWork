# Movie Database — PostgreSQL

A relational database schema and query set for movies, actors, genres, and streaming platforms.

## Overview

- Schema covers movies, actors, genres, platforms, and their relationships
- `queries/` contains SQL queries for filtering, joining, and aggregating the data
- `data/` contains seed data for all tables
- `entrypoint.d/` contains initialization scripts for Docker-based setup

## Usage

```bash
docker-compose up --build
```

Then connect to the database and run queries from the `queries/` directory.
