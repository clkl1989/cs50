-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 1) find all crime scene report regarding the theft of CS50 duck
-- select description from crime_scene_reports
-- where year = 2020 and month = 7 and day = 28
-- and street like '%Chamberlin%';
-- Clue (1): Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- 2) find 3 witnesses whose interview transcipts contain the 'courthouse' and where present during the day of theft

-- select name,transcript from interviews
-- where transcript like '%courthouse%' and year = 2020 and month = 7 and day = 28;

-- Clue (2):
-- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- 3) find suspect who drove away from courthouse parking lot within 10 minutes of theft (July 28, 2020, 10:15am)
-- 3.1) Create a table with suspects from clue by Ruth
-- create table suspect_list_1 as
-- select people.id, people.name from people
-- join courthouse_security_logs on people.license_plate = courthouse_security_logs.license_plate
-- where activity = 'exit' and year = 2020 and month = 7 and day = 28 and hour = 10 and minute < 27 and minute > 14;

-- 4) find suspect who was withdrawing money at ATM on Fifer Street before the theft (July 28, 2020, 10:15am)
-- create table suspect_list_2 as
-- select people.id, people.name from people
-- join bank_accounts on people.id = bank_accounts.person_id
-- join atm_transactions on bank_accounts.account_number = atm_transactions.account_number
-- where year = 2020 and month = 7 and day = 28 and transaction_type = 'withdraw' and atm_location = 'Fifer Street';

-- 5) find suspect who called someone while leaving the courthouse and was planning to take the earlierst flight out of Fiftyville on July 29, 2020. The flight ticket is purchased by the callee (the person whom the thief called)
-- create table suspect_list_3 as
-- -- 5.1) people who called someone while leaving the courthouse
-- select people.id, people.name from people
-- join phone_calls on people.phone_number = phone_calls.caller
-- where year = 2020 and month = 7 and day = 28
-- INTERSECT

-- 5.2) people who took earliest flight out of Fiftyville on July 29, 2020
-- select people.id, people.name from people
-- join passengers on people.passport_number = passengers.passport_number
-- where flight_id in (select flights.id from flights
-- join airports on flights.origin_airport_id = airports.id
-- where airports.city = 'Fiftyville' and year = 2020 and month = 7 and day = 29
-- order by hour, minute
-- limit 1);

-- 5.3) identify earliest flight out of Fiftyville on July 29, 2020
-- select flights.id from flights
-- join airports on flights.origin_airport_id = airports.id
-- where airports.city = 'Fiftyville' and year = 2020 and month = 7 and day = 29
-- order by hour, minute
-- limit 1;

--6) Find id and name that appears in all 3 suspect list >> this person is the THIEF
-- select id, name from people
-- where id in (
-- select id from suspect_list_1
-- intersect
-- select id from suspect_list_2
-- intersect
-- select id from suspect_list_3);

--7) Where the thief escape to?
-- select city from airports
-- join flights on flights.destination_airport_id = airports.id
-- where flights.id in (select flights.id from flights
-- join airports on flights.origin_airport_id = airports.id
-- where airports.city = 'Fiftyville' and year = 2020 and month = 7 and day = 29
-- order by hour, minute
-- limit 1);

--8) Who is the accomplice (the person whom the theif called)

--8.1) Receivers who got calls from theif on 28 July 2020 and the call was less than 1 minute (60s)

select people.id, people.name from people
where people.phone_number in
(
select receiver from phone_calls
join people on phone_calls.caller = people.phone_number
where year = 2020 and month = 7 and day = 28 and duration < 60 and people.id in (
select id from suspect_list_1
intersect
select id from suspect_list_2
intersect
select id from suspect_list_3));