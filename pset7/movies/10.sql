-- In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
-- Your query should output a table with a single column for the name of each person.

select people.name
from movies
join ratings on movies.id = ratings.movie_id
join directors on movies.id = directors.movie_id
join people on directors.person_id = people.id
where ratings.rating >= 9.0 group by people.id;