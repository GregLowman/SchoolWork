SELECT movies.name, movies.imbd_rating 
FROM movies 
ORDER BY imbd_rating 
DESC LIMIT 1;


/*
        name         | imbd_rating
---------------------+-------------
 Saban, Son of Saban |          10
(1 row)
*/