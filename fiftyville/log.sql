-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Only intially know that theft took place on July 28, 2020 and took place on Chamberlin Street

-- Start with crime_scene_reports - Check report that mataches date and location of the crime
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";

-- Time: 10:15 am, Chamberlin courthouse. 3 witnesses - interview transcript mentions courthouse

-- Check interviews - Taken on day of crime and feature courthouse
SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28
INTERSECT
SELECT name, transcript FROM interviews WHERE transcript LIKE "%courthouse%";
-- Clues
-- Ruth - Within 10 min of theft (10:15 - 10:25 am) - thief got into car @ courthouse parking lot - look at cars that left parking lot in time frame.
-- Eugene - Passed ATM @ Fifer St. and saw thief withdrawing money.
-- Raymond - Thief called someone - less than a minute conversation. Earliest flight out of Fiftyville tomorrow - 7/29/2020.
-- Person on phone - purchase flight ticket - accomplice

-- The person table contains an id, name, phone_number, passport_number, and license plate

-- 1) Check thief's car leaving courthouse parking lot (10:15 am - 10:25 am)
-- Compare license_plate from people and from courthouse_security_logs
SELECT name FROM people
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute < 25 AND activity = "exit"
INTERSECT
-- 2) Check ATM withdraws at Fifer Street
-- Compare ATM account number with bank account number that corresponds to a person
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"
INTERSECT
-- 3) Check phone_calls with duration less than a minute and check for reciever
-- Phone number to caller for thief
SELECT name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE month = 7 AND day = 28 AND duration <= 60
-- 4) Check for flight out of Fiftyville on 7/29/2020 - ordering by earliest flights available and check for destination of flight
-- Passport_number to thief -- Passport_number to passenger to flight_id to flight with specified information - earliest flight
INTERSECT
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE flight_id = (SELECT id FROM flights WHERE month = 7 AND day = 29 ORDER BY hour);

-- Get thief phone_number to get accomplice
SELECT phone_number FROM people WHERE name = "Ernest";
SELECT name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE caller = "(367) 555-5533" AND month = 7 AND day = 28 AND duration <= 60;

-- Get destination city from name of thief
SELECT city FROM airports
JOIN flights ON airports.id = destination_airport_id
JOIN passengers ON flights.id = flight_id
JOIN people ON passengers.passport_number = people.passport_number
WHERE name = "Ernest";





