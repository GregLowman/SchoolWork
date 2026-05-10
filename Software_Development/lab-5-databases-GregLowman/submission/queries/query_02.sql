SELECT movies.name, actors.name 
FROM movies 
JOIN movies_to_actors ON movies_to_actors.movie_id = movies.id 
JOIN actors ON actors.id = movies_to_actors.actor_id 
WHERE actors.name = 'Leonardo di Caprio';

/*
                  name                   |        name
-----------------------------------------+--------------------
 Midsummer Night's Sex Comedy, A         | Leonardo di Caprio
 Secret Honor                            | Leonardo di Caprio
 Ballad of a Soldier (Ballada o soldate) | Leonardo di Caprio
 Satan's Tango (Sátántangó)              | Leonardo di Caprio
 Miracle                                 | Leonardo di Caprio
 Smoke Signals                           | Leonardo di Caprio
 Shutter Island                          | Leonardo di Caprio
(7 rows)
*/