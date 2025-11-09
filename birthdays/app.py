from cs50 import SQL
from flask import Flask, render_template, request

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


def render(answer_type, answer):
    # Get the list of birthdays dict
    birthdays = db.execute("SELECT * FROM birthdays")
    # Call the main page with the appropriate message
    return render_template("index.html", answer_type=answer_type, answer=answer, birthdays=birthdays)


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # Define answer type
        answer_type = request.form.get("form_id")
        # Get the input name
        personName = request.form.get("personName")
        # If empty, then reload the page with the message that the person name is mandatory
        if not personName:
            return render(answer_type, "Name is mandatory")

        # Check if the name is not already in the DB
        result = db.execute("SELECT * FROM birthdays WHERE name = ?", personName)
        if len(result) > 0:
            if answer_type == "add":
                return render(answer_type, f"{personName} already exists in the database")
            elif answer_type == "delet":
                db.execute("DELETE FROM birthdays WHERE name = ?", personName)
                return render(answer_type, f"{personName} removed from the database")

        elif answer_type == "edit" or answer_type == "delet":
            return render(answer_type, f"{personName} cannot be {answer_type}ed as he or she does not exist in the database")

        # Check month's presence and validity
        month = request.form.get("month")
        if not month:
            return render(answer_type, "Month is mandatory")
        if not (1 <= int(month) <= 12):
            return render(answer_type, "Not a valid month")

        # Check day's presence and validity
        day = request.form.get("day")
        if not day:
            return render(answer_type, "Day is mandatory")
        if not (1 <= int(day) <= 31):
            return render(answer_type, "Not a valid day")

        # If input data is valid, insert/update date in the DB
        if answer_type == "add":
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?);",
                       personName, month, day)
        elif answer_type == "edit":
            db.execute("UPDATE birthdays set month = ?, day = ? where name = ?;",
                       month, day, personName)

        return render(answer_type, f"{personName}'s birthday {answer_type}ed in the database with {month}/{day} date")

    else:
        return render("", "")
