sen = input("Text: ")

word = 0
letter = 0
sentence = 0

for i in sen:

    if i.isalpha() == True:  # see if i is letter or no
        letter += 1

    if i == " ":
        word += 1

    if i == "." or i == "!" or i == "?":
        sentence += 1

# calculations
a_sentences = round(((sentence / (word+1)) * 100), 2)
a_letters = round(((letter / (word+1)) * 100), 2)

index = 0.0588 * a_letters - 0.296 * a_sentences - 15.8

# output
if round(index) >= 16:
    print("Grade 16+")
    
elif round(index) <= 1:
    print("Before Grade 1")
    
else:
    print(f"Grade {round(index)}")