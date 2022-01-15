CREATE TABLE portfolio (id INTEGER, user_id INTEGER, symbol TEXT, company TEXT, shares INTEGER, price NUMERIC, total NUMERIC, PRIMARY KEY(id), FOREIGN KEY(user_id) REFERENCES users(id));
CREATE TABLE history (id INTEGER, user_id INTEGER, symbol TEXT, shares INTEGER, price NUMERIC, transaction_date TEXT, transaction_type TEXT, PRIMARY KEY(id),FOREIGN KEY(user_id) REFERENCES users(id));
