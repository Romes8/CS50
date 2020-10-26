import csv
from cs50 import SQL
from sys import argv

if len(argv) < 2:
    print("Error")
    exit()


db = SQL("sqlite:///students.db")

with open(argv[1], "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        name = row["name"]
        house = row["house"]
        birth = row["birth"]

        print(f"name: {name}")
        Fullname = name.split(" ")

        if len(Fullname) > 2:
           # print(F"First name: {Fullname[0]}, Middle name: {Fullname[1]}, Last name: {Fullname[2]}, House: {house}, birth: {birth}")

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       Fullname[0], Fullname[1], Fullname[2], house, birth)

        else:
            #print(F"First name: {Fullname[0]}, Middle name: None , Last name: {Fullname[1]}")

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       Fullname[0], None, Fullname[1], house, birth)

print("Succesfull")