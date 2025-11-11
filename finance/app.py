import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# --------------------------------------------------------------------------------------------------
# HOME route
# --------------------------------------------------------------------------------------------------


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get user ID from session
    userId = session.get("user_id")

    # Query database for username
    user_rows = db.execute(
        "SELECT username, cash FROM users WHERE id = ?", userId)
    username = user_rows[0]["username"]
    cash_balance = user_rows[0]["cash"]

    # Query database for user's portfolio in history table
    portfolio_rows = db.execute(
        "SELECT symbol, SUM(shares) AS sum_shares FROM history WHERE userid = ? GROUP BY symbol HAVING sum_shares > 0", userId)
    # Define portfolio list
    portfolio = []

    # Intialize total portfolio value
    total_pf_value = 0.0

    # for each stock symbol in portfolio_rows, get data and look up current price and calculate total value
    for row in portfolio_rows:
        symbol = row["symbol"]
        shares = row["sum_shares"]
        # Look up current price
        quote = lookup(symbol)
        # If a match is found, calculate total position value and append to portfolio list
        if quote:
            pos_value = int(shares) * float(quote["price"])
            total_pf_value += pos_value
            portfolio.append({
                "symbol": symbol,
                "shares": shares,
                "price": usd(quote["price"]),
                "position_value": usd(pos_value),
            })

    # Render index.html with username, cash balance and portfolio
    return render_template("index.html",
                           username=username,
                           cash_display=usd(cash_balance),
                           portfolio=portfolio,
                           total_balance_value=usd(cash_balance + total_pf_value))


# --------------------------------------------------------------------------------------------------
# BUY route
# --------------------------------------------------------------------------------------------------
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # Get user ID from session
    userId = session.get("user_id")
    # Get user cash balance
    cash = float(db.execute("SELECT cash FROM users WHERE id = ?", userId)[0]["cash"])
    cash_display = usd(cash)

    if request.method == "POST":
        # Store the stock symbol
        symbol = (request.form.get("symbol")).upper()
        if not symbol:
            return apology("Stock symbol is mandatory")
        # Get current price if the stock is valid
        quote = lookup(symbol)
        if not quote:
            return apology("Not a valid symbol. No quote found")
        # Get number of shares to buy
        shares = request.form.get("shares")
        # Check that the number of shares is a proper positive integer
        if not shares.isdigit() or int(shares) <= 0:
            return apology("Please insert a positive integer as number of shares")

        # Compute total price
        stock_price = float(quote["price"])
        total_price = int(shares) * stock_price
        total_price_display = usd(total_price)

        # Check for enough founds and return error if not total price is higher than available founds
        if total_price > cash:
            return apology(
                f"Not enough cash, you are trying to buy for {total_price_display} of stocks while you have only {cash_display} of cash in your portfolio")

        # Compute timestamp
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M")
        # Proceed with buy operation
        db.execute(
            "INSERT INTO history (userid, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?);",
            userId,
            symbol,
            shares,
            stock_price,
            timestamp
        )
        # Update user's cash balance
        db.execute(
            "UPDATE users SET cash = cash - ? WHERE id = ?;",
            total_price,
            userId
        )

        return redirect("/")
        # return apology(f"You are trying to buy {shares} shares of {symbol} for a total amount of {total}")

    else:
        return render_template("buy.html", cash=cash_display)

# --------------------------------------------------------------------------------------------------
# HISTORY route
# --------------------------------------------------------------------------------------------------


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get user id
    userId = session.get("user_id")
    # Get history for this user
    history_db = db.execute(
        "SELECT * FROM history WHERE userid = ? order by id DESC;", userId
    )

    # Initialize history list
    history_list = []
    # Loop on each row and add them to the history list to be passed to the template
    for entry in history_db:

        datetime = entry["timestamp"]
        symbol = entry["symbol"]
        shares = int(entry["shares"])
        bs = "Buy" if shares > 0 else "Sell"
        price = float(entry["price"])
        total = shares * price

        history_list.append({
            "transacted": datetime,
            "symbol": symbol,
            "bs": bs,
            "shares": shares,
            "price": usd(price),
            "total": usd(total),
        })

    return render_template("history.html", history_list=history_list)

# --------------------------------------------------------------------------------------------------
# LOGIN route
# --------------------------------------------------------------------------------------------------


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

# --------------------------------------------------------------------------------------------------
# LOGOUT route
# --------------------------------------------------------------------------------------------------


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

# --------------------------------------------------------------------------------------------------
# QUOTE route
# --------------------------------------------------------------------------------------------------


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        # Store the stock symbol
        symbol = (request.form.get("symbol")).upper()
        if not symbol:
            return apology("Stock symbol is mandatory")
        # Get current price if the stock is valid
        quote = lookup(symbol)
        if not quote:
            return apology("Not a valid symbol. No quote found")
        # Render quote.html with quote data
        return render_template("quoted.html",
                               name=quote["name"],
                               symbol=quote["symbol"],
                               price=usd(quote["price"]))
    else:
        return render_template("quote.html")


# --------------------------------------------------------------------------------------------------
# REGISTER route
# --------------------------------------------------------------------------------------------------
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get user name from the form
        username = request.form.get("username")

        # Ensure username was submitted
        if not username:
            return apology("must provide username")

        # Get user password from the form
        password = request.form.get("password")
        # Ensure password was submitted
        if not password:
            return apology("must provide password")

        # Ensure confirmation password was submitted
        if not request.form.get("confirmation"):
            return apology("must confirm password")

        # Ensure password and confirmation match
        if password != request.form.get("confirmation"):
            return apology("passwords do not match")

        # If everything is ok, get the hash of the user's password and insert the data into the db
        # (Keep the default cash value to 10000)
        hashed_password = generate_password_hash(password)
        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?);",
                username,
                hashed_password,
            )
        except Exception as e:
            return apology("username already exists")

        # Once registered, log the user in automatically
        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?;", username
        )
        session["user_id"] = rows[0]["id"]

        # And redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

# --------------------------------------------------------------------------------------------------
# SELL route
# --------------------------------------------------------------------------------------------------


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
  # Get user ID from session
    userId = session.get("user_id")
    # Get list of stocks owned by the user and their total shares
    owned_stocks = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM history WHERE userid = ? GROUP BY symbol HAVING total_shares > 0;",
        userId
    )

    if request.method == "POST":
        # Store the stock symbol
        symbol = (request.form.get("symbol")).upper()
        if not symbol:
            return apology("Stock symbol is mandatory")
        # Get current price if the stock is valid
        quote = lookup(symbol)
        if not quote:
            return apology("Not a valid symbol. No quote found")
        # Get number of shares to buy
        shares = request.form.get("shares")
        # Check that the number of shares is a proper positive integer
        if not shares.isdigit() or int(shares) <= 0:
            return apology("Please insert a positive integer as number of shares")
        # Check that the number of shares is lower or equal to the owned shares
        owned_shares = 0
        for stock in owned_stocks:
            if stock["symbol"] == symbol:
                owned_shares = int(stock["total_shares"])
                break
        if int(shares) > owned_shares:
            return apology(f"You are trying to sell {shares} shares of {symbol} while you own only {owned_shares} shares")

        # Proceed with sell operation
        # Compute total price
        stock_price = float(quote["price"])
        total_price = int(shares) * stock_price
        negative_shares = -int(shares)
        total_price_display = usd(total_price)

        # Compute timestamp
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M")

        db.execute(
            "INSERT INTO history (userid, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?);",
            userId,
            symbol,
            negative_shares,
            stock_price,
            timestamp
        )
        # Update user's cash balance
        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?;",
            total_price,
            userId
        )

        return redirect("/")

    else:
        return render_template("sell.html", owned_stocks=owned_stocks)
