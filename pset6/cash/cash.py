
from time import sleep

qurt = 0
dime = 0
nic = 0
peni = 0

while True:
    try:
        sum = float(input("Insert payment:"))

        if sum < 0:
            continue

        else:
            sum = sum * 100
            break

    except ValueError:
        continue

while sum != 0:
    if sum >= 25:
        sum = sum - 25
        qurt += 1

    elif sum >= 10 and sum < 25:
        sum = sum - 10
        dime += 1

    elif sum >= 5 and sum < 10:
        sum = sum - 5
        nic += 1

    else:
        sum = sum - 1
        peni += 1

print(f"Total coins: {qurt + dime + nic + peni}")