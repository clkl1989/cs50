/*determine the average rating of all movies released in 2012.*/

select avg(rating) from ratings
join movies on movies.id = ratings.movie_id
where year = 2012;