SELECT movies.name 
FROM movies 
JOIN movies_to_genres ON movies_to_genres.movie_id = movies.id 
JOIN genres ON genres.id = movies_to_genres.genre_id 
WHERE genres.name = 'Thriller' 
ORDER BY movies.gross_revenue DESC 
LIMIT 3;

/*
      name
----------------
 Shutter Island
 Mammy
 Cover-Up
(3 rows)

*/