SELECT actors.name 
FROM actors 
JOIN movies_to_actors ON movies_to_actors.actor_id = actors.id 
GROUP BY actors.id, actors.name 
ORDER BY COUNT(movies_to_actors.movie_id) DESC 
LIMIT 1;

/*
        name
--------------------
 Leonardo di Caprio
(1 row)

movies_db=#
*/
