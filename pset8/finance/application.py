import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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

    rows = db.execute("SELECT * FROM stocks WHERE user_id = :user", user = session['user_id'])

    cash = db.execute("SELECT cash FROM users WHERE id = :user", user = session['user_id'])[0]['cash']

    total = cash
    stocks = []

    for index,row in enumerate(rows):
        symbol = lookup(row['symbol'])

        stocks.append(list((symbol['symbol'], symbol['name'], row['amount'], symbol['price'], round(symbol['price'] * row['amount'], 2))))
        total += stocks[index][4]

    return render_template("index.html", stocks = stocks, cash = round(cash,2), total = round(total,2))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "POST":

        amount=int(request.form.get("shares"))
        symbol=lookup(request.form.get("symbol"))['symbol']


        if not lookup(symbol):
            return apology("Could not find the stock")


        price=lookup(symbol)['price']

        cash = db.execute("SELECT cash FROM users WHERE id = :username ", username = session['user_id'])[0]['cash']

        after = cash - price * float(amount)

        if after < 0:
            return apology("Not enough money.")

        stocks = db.execute("SELECT amount FROM stocks WHERE user_id = :user AND symbol = :symbol", user = session['user_id'], symbol = symbol)

        if not stocks:
            db.execute("INSERT INTO stocks(user_id,amount,symbol) VALUES(:user, :amount, :symbol)", user = session['user_id'], amount = amount, symbol = symbol)

        else:
            amount += stocks[0]['amount']
            db.execute("UPDATE stocks SET amount= :amount WHERE user_id = :user AND symbol = :symbol", amount = amount,user = session['user_id'] ,symbol = symbol)

        db.execute("UPDATE users SET cash = :cash WHERE id = :user", cash = after , user = session['user_id'])

        final_price = round(float(amount) * price)

        db.execute("INSERT INTO transactions (user_id, stock, amount, price) VALUES(:user, :stock, :amount, :price)",
                    user=session['user_id'], stock = symbol, amount = amount, price = -final_price)


        flash("Sucessfully bought !")

        return redirect("/")

    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():

    rows = db.execute("SELECT * FROM transactions WHERE user_id = :user", user = session['user_id'])

    transactions = []
    for row in rows:
         info = lookup(row['stock'])

         transactions.append(list((info['symbol'], info['name'], row['amount'], row['price'], row['time'])))
    return render_template("history.html", transactions = transactions)




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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash("Welcome !")
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
    if request.method == "POST":

        stock = lookup(request.form.get("symbol"))

        if not stock:
            return apology("SAIK stock")

        return render_template("quote.html", stock=stock)

    else:
        return render_template("quote.html", stock="")


@app.route("/register", methods=["GET", "POST"])
def register():

    session.clear()

    if request.method == "POST":

        if not request.form.get("username"):
           return apology("Username needs to be filled.", 403)

        elif not request.form.get("password"):
           return apology("Password needs to be filled.", 403)

        elif request.form.get("password") != request.form.get("conf_password"):
            return apology ("Passwords dont match. Confirm password.", 403)

        elif db.execute("SELECT * FROM users WHERE username = :username", username = request.form.get("username")):
            return apology ("This name is already taken.", 403)


        db.execute("INSERT INTO users (username,hash) VALUES(:username, :password)", username = request.form.get("username"), password = generate_password_hash(request.form.get("password")))

        rows = db.execute("SELECT * FROM users WHERE username = :username ", username = request.form.get("username"))

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    if request.method == 'POST':

        amount = int(request.form.get('shares'))
        symbol = lookup(request.form.get('symbol'))['symbol']

        if not amount:
            return apology("Select amount")

        if not lookup(symbol):
            return apology("Select stock")

        price = lookup(symbol)['price']

        cash = db.execute("SELECT cash FROM users WHERE id = :user", user = session['user_id'])[0]['cash']

        after_cash = cash + price * float(amount)
        value = price * float(amount)

        ac_amount = db.execute("SELECT amount FROM stocks WHERE user_id = :user AND symbol = :symbol" , user = session['user_id'], symbol = symbol)[0]['amount']

        if ac_amount < amount:
            return apology("You dont own enough stocks.")

        after_stock = ac_amount - amount

        db.execute("UPDATE stocks SET amount = :amount WHERE user_id = :user AND symbol = :symbol",
                user = session['user_id'], symbol = symbol, amount = after_stock )

        db.execute("INSERT INTO transactions (user_id, stock, amount, price)  VALUES(:user, :stock, :amount, :price) ",
                user = session['user_id'],stock = symbol ,amount = -amount, price = round(value, 2))

        db.execute("UPDATE users SET cash = :cash WHERE id = :user", cash = after_cash, user = session['user_id'])

        if after_stock == 0:
            db.execute("DELETE FROM stocks WHERE user_id = :user AND symbol = :symbol ", user = session['user_id'], symbol = symbol)

        flash("Sold sucessfully !")
        return redirect("/")

    else:
        return render_template("sell.html")



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
