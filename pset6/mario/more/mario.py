counter = 1
i = 1

while i == 1:
    try:
        num = int(input("Height:"))

        if num > 8 or num < 1:
            continue
        else:
            i = 2
            break

    except ValueError:
        continue

for s in range(num):
    print(" " * (num-counter), end="")
    print("#" * counter, end="")
    print("  ", end="")
    print("#" * counter)
    counter += 1