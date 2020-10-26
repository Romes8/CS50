from csv import reader, DictReader
from sys import argv

if len(argv) < 3:
    print("error")
    exit()

with open(argv[2]) as dna_file:
    dna_reader = reader(dna_file)
    for row in dna_reader:
        dna_list = row

dna = dna_list[0]

sequences = {}

with open(argv[1]) as people_file:
    people = reader(people_file)
    for row in people:
        dna_Sequences = row
        dna_Sequences.pop(0)
        break

for item in dna_Sequences:
    sequences[item] = 1

for key in sequences:
    length = len(key)
    temp_Max = 0
    temp = 0
    for i in range(len(dna)):

        while temp > 0:
            temp -= 1
            continue
        if dna[i: i + length] == key:
            while dna[i - length: i] == dna[i: i + length]:
                temp += 1
                i += length
            if temp > temp_Max:
                temp_Max = temp

    sequences[key] += temp_Max

with open(argv[1], newline='') as people_file:
    people = DictReader(people_file)
    for person in people:
        match = 0

        for dna in sequences:
            if sequences[dna] == int(person[dna]):
                match += 1
        if match == len(sequences):
            print(person['name'])
            exit()

    print("No match")