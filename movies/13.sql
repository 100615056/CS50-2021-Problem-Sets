SELECT DISTINCT(name) from movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE movie_id IN
(SELECT movie_id FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE name = "Kevin Bacon" AND birth = 1958)
AND person_id NOT IN
(SELECT ID FROM people
WHERE name = "Kevin Bacon" AND birth = 1958)
GROUP BY name;