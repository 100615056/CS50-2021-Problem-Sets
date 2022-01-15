import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    transactions = db.execute("SELECT * FROM portfolio WHERE user_id=:user_id", user_id=session["user_id"])
    rows = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
    cash = rows[0]["cash"]
    return render_template("index.html", transactions=transactions, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Ensure symbol was entered
        if not request.form.get("symbol"):
            return apology("must provide symbol")
        # Ensure valid symbol was entered
        result = lookup(request.form.get("symbol"))
        if not result:
            return apology("invalid symbol")
        # Ensure share value is entered
        if not request.form.get("shares"):
            return apology("must provide share")
        # Ensure positive integer is entered
        share = request.form.get("shares")
        try:
            share = int(share)
            if share < 0:
                return apology("must provide positive integer")
        except ValueError:
            return apology("must provide shares as an integer")

        shares = float(request.form.get("shares"))
        company = result['name']
        price = float(result['price'])
        symbol = result['symbol']

        total_purchase = float(price * shares)

        # Check if cash is available
        rows = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        current = float(rows[0]["cash"])
        if current < total_purchase:
            return apology("not enough cash")

        # Calculate remaining cash and buy stock - flash bought message
        # Update cash and transaction data
        cash = float(current - total_purchase)
        db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=cash, id=session["user_id"])
        flash('Bought')

        # Calculate transaction date and time
        # Source: https://www.programiz.com/python-programming/datetime/current-datetime
        now = datetime.now()
        time = now.strftime("%Y-%m-%d %H:%M:%S")

        # Fill in portfolio table
        db.execute("INSERT INTO portfolio (price, total, shares, company, symbol, user_id) VALUES (:price, :total, :shares, :company, :symbol, :user_id)", price=usd(
            price), total=usd(total_purchase), shares=shares, company=company, symbol=symbol, user_id=session["user_id"])

        # Fill in History table
        db.execute("INSERT INTO history (transaction_type, transaction_date, price, shares, symbol, user_id) VALUES (:transaction_type, :transaction_date, :price, :shares, :symbol, :user_id)", transaction_type='buy', transaction_date=time, price=usd(
            price), shares=shares, symbol=symbol, user_id=session["user_id"])

        # Create template with new information
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM history WHERE user_id=:user_id", user_id=session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Ensure symbol was entered
        if not request.form.get("symbol"):
            return apology("must provide symbol")
        # Ensure valid symbol was entered
        result = lookup(request.form.get("symbol"))
        if not result:
            return apology("invalid symbol")

        name = result['name']
        price = usd(result['price'])
        symbol = result['symbol']
        return render_template("quoted.html", name=name, price=price, symbol=symbol)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Error Checking

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")
        username = request.form.get("username")
        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Check if username already exists
        if len(rows) == 1:
            return apology("username already exists")

        # Check if password matches confirmed password
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match")

        # Validate password combination
        if len(request.form.get("password")) not in range(6, 11):
            return apology('length betwen 6 to 10 characters')
        if not re.search('[0-9]', request.form.get("password")):
            return apology('Need at least one number')
        if not re.search('[a-zA-Z]', request.form.get("password")):
            return apology('Need at least one letter')
        if not re.search('[a-z]', request.form.get("password")):
            return apology('Need at least one lower letter')
        if not re.search('[A-Z]', request.form.get("password")):
            return apology('Need at least one uppercase letter')
        if not re.search('[!@#$%^&*]', request.form.get("password")):
            return apology("Need a special character")
        if re.search('[,.;:]', request.form.get("password")):
            return apology("Invalid character")

        password = request.form.get("password")

        # Enter user into database
        hashed = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hashed)

        # Redirect user to home page
        return redirect("/")

    else:
        # User reached route via GET (as by clicking a link or via redirect)
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Ensure symbol was entered
        if not request.form.get("symbol"):
            return apology("must provide symbol")
        # Ensure valid symbol was entered
        result = lookup(request.form.get("symbol"))
        if not result:
            return apology("invalid symbol")
        # Ensure share value is entered
        if not request.form.get("shares"):
            return apology("must provide share")
        # Ensure positive integer is entered
        share = request.form.get("shares")
        try:
            share = int(share)
            if share < 0:
                return apology("must provide positive integer")
        except ValueError:
            return apology("must provide shares as an integer")

        shares = float(request.form.get("shares"))

        # Validate request matches values from database
        rows = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id", user_id=session["user_id"])
        # Ensure share belongs to user
        stored_shares = float(rows[0]["shares"])
        if shares > stored_shares:
            return apology("must provide purchased share")

        company = result['name']
        price = float(result['price'])
        symbol = result['symbol']

        total_purchase = float(price * shares)
        shares_remain = float(stored_shares - shares)

        # Update cash
        Rows = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        current = float(Rows[0]["cash"])
        cash = float(current + total_purchase)
        db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=cash, id=session["user_id"])
        flash('Sold!')

        # Calculate transaction date and time
        # Source: https://www.programiz.com/python-programming/datetime/current-datetime
        now = datetime.now()
        time = now.strftime("%Y-%m-%d %H:%M:%S")

        # Update history table with transactions
        db.execute("INSERT INTO history (transaction_type, transaction_date, price, shares, symbol, user_id) VALUES (:transaction_type, :transaction_date, :price, :shares, :symbol, :user_id)", transaction_type='sell', transaction_date=time, price=usd(
            price), shares=-shares, symbol=symbol, user_id=session["user_id"])

        # Update entry in portfolio
        if stored_shares > shares:
            db.execute("UPDATE portfolio SET price=:price, total=:total, shares=:shares WHERE user_id=:user_id", price=usd(
                price), total=usd(total_purchase), shares=shares_remain, user_id=session["user_id"])
        else:
            db.execute("DELETE FROM portfolio WHERE user_id=:user_id", user_id=session["user_id"])

        # Create template with new information
        return redirect("/")

    else:
        # Only show active shares to sell
        transactions = db.execute("SELECT * FROM portfolio WHERE user_id=:user_id", user_id=session["user_id"])
        return render_template("sell.html", transactions=transactions)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
