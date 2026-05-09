SELECT actors.name 
FROM actors 
JOIN movies_to_actors AS mta ON mta.actor_id = actors.id 
JOIN movies ON movies.id = mta.movie_id 
JOIN movies_to_genres AS mtg ON mtg.movie_id = movies.id 
JOIN genres ON genres.id = mtg.genre_id 
WHERE actors.location = 'Missouri' AND genres.name = 'Romcom' 
ORDER BY actors.name;

/*
  name
---------
 Malachi
(1 row)
*/