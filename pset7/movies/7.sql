/*list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.
Your query should output a table with two columns, one for the title of each movie and one for the rating of each movie.
Movies that do not have ratings should not be included in the result.*/

-- select movies.title, ratings.rating from movies where year = 2010 and rating is not null
-- join ratings on movies.id = ratings.movie_id
-- order by rating desc, title;

select
    movies.title,
    ratings.rating
from movies
join ratings on movies.id = ratings.movie_id
where
    year = 2010 and
    rating is not null
order by rating desc, title;