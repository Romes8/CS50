import csv
from sys import argv
from cs50 import SQL

if len(argv) < 2:
    print("Error")
    exit()


db = SQL("sqlite:///students.db")

house_name = argv[1]
print(house_name)

data = db.execute("SELECT * FROM students WHERE house = (?) ORDER BY last", argv[1])

for row in data:
    if row["middle"] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")

