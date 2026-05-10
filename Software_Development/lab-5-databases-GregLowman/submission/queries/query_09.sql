SELECT actors.id, actors.name, SUM(movies.gross_revenue) AS revenue_sum 
FROM movies 
JOIN movies_to_actors ON movies_to_actors.movie_id = movies.id 
JOIN actors ON actors.id = movies_to_actors.actor_id 
GROUP BY actors.id, actors.name 
ORDER BY revenue_sum DESC 
LIMIT 1;

/*
 id |        name        | revenue_sum
----+--------------------+-------------
 17 | Leonardo di Caprio |   298665119
(1 row)
*/