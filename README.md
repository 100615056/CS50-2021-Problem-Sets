# CS50-2021-Problem-Sets

## Problem Sets using C

### mario.c

Create a double half-pyramid using hashes (#) where the user decides the height by entering a number between 1 and 8, inclusive.

### credit.c

Prompt the user for a credit card number and determine whether it is a valid American Express, MasterCard, or Visa card number, per the definitions of each’s format herein. 

**Note:**
- Luhn's Algorithm was used to determine credit card number validity 
- Assumption: The user's input is entirely numeric.

### readability.c

Prompt the user for a text and determine the reading level using the Coleman-Liau formula.

**Note:**
- Letter - any lowercase character from a-z or any uppercase character from A-Z
- Word - Sequence of character seperated by spaces
- End of sentence - Occurence of period, exclamation point, or question mark
- If index number is 16 or higher, output is Grade16+
- If index number is less than 1, output is Before Grade 1

### caesar.c

Via command-line argument, the user determines the cipher key and supplies a string of plaintext. The program outputs the user's original string as well as the encoded text that was computed using Caesar's algorithm. 

**Note:**
- Single command-line argument - a non-negative integer less than 2^31 - 26
- Case is preserved

### plurality.c 

Simulate a plurality vote election. Complete the vote and print_winner function.

vote
- Take the name of the candidate who was voted for and if matching candidate, update vote total
- Assumption: No two candidates have the same name

winner
- Print the name of the candidates that recieved the most votes in the election
- If tie, print the names of each winning candidates

### runoff.c

Implement a runoff election. Complete the implementation of vote, tabulate, print_winner, find_min, is_tie, and eliminate functions.

vote 
- Update voter's preference in global preferences array
-  Assumption: No two candidates have the same name

tabulate
- Update number of votes of each candidate at current stage in the runoff

print_winner
- If any candidate has more than 50% of the vote, print the winner
- If nobody has won yet, return false

find_min
- Return the minimum vote total for currently running candidates

is_tie
- If every current candidate has the same number of votes, return true; otherwise return false 

eliminate
- Eliminate candidate(s) who the minimum number of votes.

### speller.c

Spell-check a file using a hash table. Implement the load, hash, size, check, and unload functions. 

load
- Takes the dictionary file, and reads the words, and loads them into hashtable

hash 
- Takes a word and return numerical index between 0 and N-1, inclusive (implement hash function)
- Deterministic
- Allowed to source hash function

size
- Return number of words in dictionary

check
- Take a word and return true if the word is in the dictionary; false otherwise
- case-insensitive

unload
- Free up allocated memory 

**Note:**
- Assumptions: 
   - dictionary passed is alphabetically sorted from top to bottom with one word per line, each of which ends with \n
   - dictionary contains at least one word, and no word will be longer than LENGTH characters
   - no duplicate words, each word will contain only lowercase alphabetical characters and possibly apostrophes, and that no word will start with an apostrophe
   - check will only be passed words that contain (uppercase or lowercase) alphabetical characters and possibly apostrophes

## Problem Sets using Python

### mario.py, credit.py, readability.py

Complete the previous C problems (mario.c, credic.c, readability.c) using Python. 

### dna.py

Implement a program that identifies a person based on thier DNA sequence. Take a sequence of DNA and a CSV file containing STR counts for a list of individuals and ouput whom the DNA (most likely) belongs to.

**Note:**
Assumptions:
- If correct arguments are provided, the first argument is the filename of a valid CSV file and the second argument us the filename of a valid text file
- 1st row of CSV file will be the column names
- STR counts will not match more than one individual

## Problem Sets using SQL

### /movies

Each file is a single SQL query that outputs the necessary data specified in each problem. Uses data from IMDb, up to the data that the database was created. 

Problems can be found here: https://cs50.harvard.edu/x/2021/psets/7/movies/

### log.sql

Write SQL queries to solve the mystery given the information from fiftyville.db.

**Note:**
- Initial Information: The theft took place on July 28, 2020 and it took place on Chamberlin Street.

## Problem Set using Python, Flask, and SQL

### /finance

Implement a web application to manage a portfolio of stocks. This tool allows for the checking of real stock prices, and will allow the user to "buy" and "sell" stocks by querying IEX for stocks' prices. Complete the implementation of register, quote, buy, index, sell, history, and a personal touch.

register

- Allows user to register for an account via a form
- Contains a username, password, and confirmation of password
- Validate user data

quote
- Allows user to lookup a stock's current price

buy
- Enables a user to buy stocks
- Validate user data
- Store information in database

index
- Display an HTML table summarizing the user's current stock portfolio 

sell
- Sell stock that the user owns
- Validate user data
- Update the database

history
- Display an HTML table summarizing the user's transactions

personal touch
- Require users' passwords to have some number of letter, numbers, and symbols
