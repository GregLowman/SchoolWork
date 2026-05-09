SELECT movies.name
FROM movies 
JOIN platforms ON platforms.id = movies.platform_id 
WHERE platforms.name = 'Hulu';

/*
                            name
---------------------------------------------------------------
 Shadow Riders, The
 Saban, Son of Saban
 Smoke Signals
 American History X
 Cabinet of Dr. Caligari, The (Cabinet des Dr. Caligari., Das)
 Dawn Rider, The
 SharkTale
(7 rows)
*/