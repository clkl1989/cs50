-- In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
-- Your query should output a table with a single column for the name of each person.
-- There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
-- Kevin Bacon himself should not be included in the resulting list.

-- select stars in movies starring Kevin Bacon
select distinct people.name from stars
join people on stars.person_id = people.id
where person_id not in (select distinct person_id from stars join people on stars.person_id = people.id
where people.name = 'Kevin Bacon' and people.birth = 1958)
and movie_id in (select movie_id from stars
join people on stars.person_id = people.id
where people.name = 'Kevin Bacon' and people.birth = 1958)
order by people.name;


-- find Kevin Bacon person_id
-- select distinct person_id from stars join people on stars.person_id = people.id
-- where people.name = 'Kevin Bacon' and people.birth = 1958