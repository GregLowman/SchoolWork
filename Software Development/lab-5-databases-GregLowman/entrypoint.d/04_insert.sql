INSERT INTO movies (id, name, duration, year_of_release, gross_revenue, country, language, imbd_rating, platform_id) VALUES (27,'Shrek', 120, 2001, 1000000, 'America', 'English', 9.4, 1), (28,'SharkTale', 200, 2003, 2000934, 'America', 'English', 9.0, 6);

--INSERT 0 2

INSERT INTO genres (id, name) Values (9, 'Horror'), (10, 'Zombie');

--INSERT 02

INSERT INTO actors (id, name, agency, active_since, location) Values (21, 'Mike Myers', 'MikeFilms', 1995, 'California'), (22, 'Will Smith','SmithMovies', 1980, 'Texas');

--INSERT 02

INSERT INTO platforms (id, name, viewership_cost) VALUES (9, 'fubu', 200.2), (10, 'youtube', 260.2);

--INSERT 02

INSERT INTO movies_to_actors (movie_id, actor_id) VALUES (27, 21), (28, 22);

--INSERT 02

INSERT INTO movies_to_genres (movie_id, genre_id) VALUES (27, 3), (28, 3);

--INSERT 02