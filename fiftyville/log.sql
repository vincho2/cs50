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

-- Get bakery security log
SELECT * FROM bakery_security_logs
WHERE year = 2024 AND month = 7 AND day = 28
AND activity = 'exit';

-- Get ATM's info

-- Find people that called someone less than a minute on the theft day and having left the parking lot
-- of the bakery on the same day (5 results)
SELECT DISTINCT(pp.name), pp.passport_number, bnk. FROM phone_calls ph, people pp, bakery_security_logs bkl, bank_account bnk
WHERE 1=1
AND ph.caller = pp.phone_number
AND bkl.license_plate = pp.license_plate
AND bkl.year = 2024
AND bkl.month = 7
AND bkl.day = 28
AND ph.year = 2024
AND ph.month = 7
AND ph.day = 28
AND ph.duration < 60
AND bnk.person_id = pp.id
;
