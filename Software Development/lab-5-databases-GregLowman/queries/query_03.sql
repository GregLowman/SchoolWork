SELECT movies.name, movies.year_of_release 
FROM movies 
ORDER BY year_of_release 
ASC LIMIT 3;

/*
                 name                  | year_of_release
---------------------------------------+-----------------
 Mammy                                 |            1988
 Angus                                 |            1991
 Miguel and William (Miguel y William) |            1992
(3 rows)

*/
