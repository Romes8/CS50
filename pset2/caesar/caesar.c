#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string sentence, output;
int numbers, shifted, key;
int n;
const char *x;
int atoi(const char *string);
int counter = 0;

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error\n");
        return 1;
    }
    x = argv[1];

    key = atoi(x);
        
    if (key == 0)
    {
        printf("Error 2\n");
        return 2;
    }
   
    do
    {
        if (key > 25)
        {
            key = key - 26;
        }
    }
    while (key > 25);
    
    sentence =  get_string("plaintext: ");

    n = strlen(sentence);
    
    printf("ciphertext: ");

    for (int i = 0; i < n; i++)
    {
        //printf("Numbers: %i \n", tolower((int)sentence[i]));
        numbers = ((int)sentence[i]);
        if ((numbers >= 97 && numbers <= 122))
        {
            
            shifted = numbers + key;
            
            if (shifted > 122)
            {
                shifted = shifted - 26;
            }
            else if ((shifted - key) <= 96 || (shifted - key) >= 123)
            {
                shifted = shifted - key;
            }
            
            printf("%c", (char)shifted);
        }
        else if (numbers >= 65 && numbers <= 90)
        {
            shifted = numbers + key;
            if (shifted > 90)
            {
                shifted = shifted - 26;
            }
            else if ((shifted - key) <= 64 || (shifted - key) >= 91)
            {
                shifted = shifted - key;
            }
            
            printf("%c", (char)shifted);
        }
        else 
        {
            shifted = numbers + 0;
            printf("%c", (char)shifted);
        }
    }
    printf("\n");
    return 0;
}