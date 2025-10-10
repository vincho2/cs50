SELECT m.title FROM movies m
JOIN stars s1 ON s1.movie_id = m.id
JOIN stars s2 ON s2.movie_id = m.id
JOIN people p1 ON p1.id = s1.person_id
JOIN people p2 ON p2.id = s2.person_id
WHERE p1.name = 'Bradley Cooper'
AND p2.name = 'Jennifer Lawrence';


