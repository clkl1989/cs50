/*lists the names of songs that are by Post Malone*/
SELECT songs.name FROM songs
JOIN artists on songs.artist_id = artists.id
WHERE artists.name = "Post Malone";