SELECT AVG(energy) as average_energy FROM songs
JOIN artists ON artists.id = songs.artists_id
WHERE artists.name = 'Drake';

