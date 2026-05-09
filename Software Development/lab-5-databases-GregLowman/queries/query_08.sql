SELECT platforms.name, COUNT(*) AS movie_count 
FROM movies 
JOIN platforms ON platforms.id = movies.platform_id 
GROUP BY platforms.id, platforms.name 
ORDER BY movie_count DESC 
LIMIT 1;

/*
  name   | movie_count
---------+-------------
 Netflix |          10
(1 row)

*/