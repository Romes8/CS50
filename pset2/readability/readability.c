#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

string text;
int length, letters;
int sentence_count;
int word_count, new_index;
int letter_counter, letter_big, letter_small;
string input;
float L, S, index;
int n = 0;


int main(void)
{
    text = get_string("Give me your text:");

    n = strlen(text);

    for (int i = 0; i < n; i++)
    {
        if ((char) text[i] == '.' || (char) text[i] == '?' || (char) text[i] == '!')
        {
            sentence_count++;
        }

        else if ((char) text[i] == ' ' && (char) text[i + 1] != ' ')
        {
            word_count++;
        }

        else if ((char) text[i] >= 'a' && (char)text[i] <= 'z')
        {
            letter_small++;
        }

        else if ((char) text[i] >= 'A' && (char)text[i] <= 'Z')
        {
            letter_big++;
        }
    }

    L = (((float)letter_big + (float)letter_small) / ((float)word_count + 1)) * 100;
    S = ((float)sentence_count / ((float)word_count + 1)) * 100;

    index = 0.0588 * L - 0.296 * S - 15.8;

    new_index = round(index);


    if (new_index > 16)
    {
        printf("Grade 16+\n");
    }

    else if (new_index < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", new_index);
    }

    /*printf("Number of sentences: %i\n", sentence_count);
    printf("Number of words: %i\n", word_count + 1);
    printf("Number of letters: %i\n", letter_big + letter_small);
    printf("Number of words per 100: %f\n", L);
    printf("Number of sentences per 100: %f\n", S);
    */




    //letters = lenght - sentence - word
}
