SELECT name FROM songs
JOIN artists ON artists.id = songs.artists_id
WHERE artists.name = 'Post Malone';
