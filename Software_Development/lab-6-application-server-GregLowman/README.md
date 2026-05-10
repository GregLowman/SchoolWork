# REST API Server — Node.js + PostgreSQL

An Express.js application server exposing REST endpoints backed by a PostgreSQL database.

## Overview

- `index.js` — Express routes for CRUD operations
- `init_data/create.sql` — database schema
- Docker Compose wires the app and database together

## Usage

```bash
docker-compose up --build
```

The API will be available at `localhost:3000`. A Postman collection is included in `Submission/` for endpoint testing.
