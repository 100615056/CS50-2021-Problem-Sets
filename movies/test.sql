SELECT movies.title FROM movies
INNER JOIN stars on movies.id = stars.movie_id
INNER JOIN people on stars.person_id = people.id
WHERE people.name = "Johnny Depp" AND people.name = "Helena Bonham Carter";