SELECT * 
FROM movies 
JOIN movies_to_genres ON movies_to_genres.movie_id = movies.id 
JOIN genres ON genres.id = movies_to_genres.genre_id 
WHERE genres.name = 'Thriller' 
ORDER BY movies.gross_revenue DESC 
LIMIT 3;

/*
 id |      name      | duration | year_of_release | gross_revenue |    country    |         language          | imbd_rating | platform_id | movie_id | genre_id | id |   name
----+----------------+----------+-----------------+---------------+---------------+---------------------------+-------------+-------------+----------+----------+----+----------
 26 | Shutter Island |        2 |            2010 |     294805697 | United States | English                   |           8 |           1 |       26 |        7 |  7 | Thriller
 21 | Mammy          |        1 |            1988 |        938708 | Peru          | New Zealand Sign Language |           3 |           7 |       21 |        7 |  7 | Thriller
 12 | Cover-Up       |        3 |            2004 |        618728 | United States | Bislama                   |           7 |           7 |       12 |        7 |  7 | Thriller
(3 rows)

*/