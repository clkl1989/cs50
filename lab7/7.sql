/*the average energy of songs that are by Drake*/
SELECT avg(energy) from songs
JOIN artists on songs.artist_id = artists.id
WHERE artists.name = "Drake";