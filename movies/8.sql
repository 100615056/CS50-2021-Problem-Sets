SELECT name from people
JOIN stars ON people.id = person_id
JOIN movies ON movies.id = movie_id
WHERE title = "Toy Story";