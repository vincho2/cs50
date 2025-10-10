-- Keep a log of any SQL queries you execute as you solve the mystery.

-- What happened on July 28, 2024 on Hunphrey Street ?
SELECT description FROM crime_scene_reports
WHERE year = 2024 AND month = 7 AND day = 28
AND street = 'Humphrey Street';

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time –
-- each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.

-- Get interviews that mention the bakery on this day of July 28, 2024
SELECT name, transcript FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28
AND transcript LIKE '%bakery%';

-- Ruth : Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |

-- Eugene : I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- Raymond : As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.


-- Iterations (each iteration enrich the final query):
-- 1. Find people that called someone less than a minute on the theft day (8 results)
-- 2. Cross with the ones having left the parking lot of the bakery on the same day (5 results)
-- 3. Cross with and having withdrawn money as well (3 results)
-- 4. Cross with flight passengers of any flight based on passport number (still 3 results)
-- 5. Cross with actual flights on the next day (29 July) that flew from Fiftyville (3 results but we see that the earliest flight went to NYC)
SELECT DISTINCT(pp.name), psg.flight_id, psg.seat, ap1.city AS origin, fl.hour, fl.minute, ap2.city as destination,
pp.phone_number, bkl.hour, bkl.minute
FROM phone_calls ph, people pp, bakery_security_logs bkl, bank_accounts bnk,
atm_transactions atm, passengers psg, flights fl, airports ap1, airports ap2
WHERE 1=1
-- Iteration 1
AND ph.caller = pp.phone_number
AND ph.year = 2024
AND ph.month = 7
AND ph.day = 28
AND ph.duration < 60
-- Iteration 2
AND bkl.license_plate = pp.license_plate
AND bkl.year = 2024
AND bkl.month = 7
AND bkl.day = 28
AND activity = 'exit'
-- Itertaion 3
AND bnk.person_id = pp.id
AND bnk.account_number = atm.account_number
AND atm.atm_location = 'Leggett Street'
AND atm.transaction_type = 'withdraw'
AND atm.year = 2024
AND atm.month = 7
AND atm.day = 28
-- Iteration 4
AND psg.passport_number = pp.passport_number
-- Iteration 5
AND psg.flight_id = fl.id
AND fl.year = 2024
AND fl.month = 7
AND fl.day = 29
AND fl.origin_airport_id = ap1.id
AND ap1.city like ('%fiftyville%')
AND fl.destination_airport_id = ap2.id
order by fl.hour, fl.minute
;


SELECT DISTINCT(pp.name), psg.flight_id, psg.seat, ap1.city AS origin, fl.hour, fl.minute, ap2.city as destination,
pp.phone_number, pp.license_plate, bnk.account_number, pp.passport_number
FROM phone_calls ph, people pp, bakery_security_logs bkl, bank_accounts bnk,
atm_transactions atm, passengers psg, flights fl, airports ap1, airports ap2
WHERE 1=1
-- Iteration 1
AND ph.caller = pp.phone_number
AND ph.year = 2024
AND ph.month = 7
AND ph.day = 28
AND ph.duration < 60
-- Iteration 2
AND bkl.license_plate = pp.license_plate
AND bkl.year = 2024
AND bkl.month = 7
AND bkl.day = 28
-- Itertaion 3
AND bnk.person_id = pp.id
AND bnk.account_number = atm.account_number
AND atm.atm_location = 'Leggett Street'
AND atm.transaction_type = 'withdraw'
AND atm.year = 2024
AND atm.month = 7
AND atm.day = 28
-- Iteration 4
AND psg.passport_number = pp.passport_number
-- Iteration 5
AND psg.flight_id = fl.id
AND fl.year = 2024
AND fl.month = 7
AND fl.day = 29
AND fl.origin_airport_id = ap1.id
AND ap1.city like ('%fiftyville%')
AND fl.destination_airport_id = ap2.id
order by fl.hour, fl.minute
;



