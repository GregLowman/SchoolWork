/* Create a table names products with the mentioned columns
having the datatypes mentioned */
CREATE TABLE movies (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    duration SMALLINT NOT NULL,
    year_of_release SMALLINT NOT NULL,
    gross_revenue FLOAT,
    country VARCHAR(100),
    language VARCHAR(100),
    imbd_rating SMALLINT,
    platform_id SMALLINT
);

CREATE TABLE actors(
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    agency TEXT,
    active_since SMALLINT,
    location VARCHAR(100)
);

CREATE TABLE platforms (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    viewership_cost FLOAT
);

CREATE TABLE genres (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100)
);

CREATE TABLE movies_to_actors (
    movie_id INT,
    actor_id INT
);

CREATE TABLE movies_to_genres (
    movie_id INT,
    genre_id INT
); 


/*
    CREATE TABLE
    CREATE TABLE
    CREATE TABLE
    CREATE TABLE
    CREATE TABLE
    CREATE TABLE
*/