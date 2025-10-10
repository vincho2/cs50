SELECT DISTINCT(p.name) FROM people p
JOIN stars s ON s.person_id = p.id
WHERE s.movie_id IN (
    SELECT DISTINCT(movie_id) FROM stars s
    JOIN people p ON s.person_id = p.id
    WHERE p.name = 'Kevin Bacon' and p.birth = 1958)
AND p.name <> 'Kevin Bacon';
