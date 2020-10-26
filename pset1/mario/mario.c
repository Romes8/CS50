#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    int x;
    int first;
    int second;
    int result;
    int counter = 1;
    int counter2 = 1;
    int counter3 = 1;
    
    do
    {
        n = get_int("Number: \n");
        if (n > 0)
        {
            first = 1;
        }

        if (n < 9)
        {
            second = 1;
        }
        result = first + second;
        /// printf("Result is: %i\n",result);
    }
    while (result != 2);

    for (int i = 0; i < n; i++)
    {
        for (int space = 0; space < (n - counter); space++)
        {
            printf(" ");
        }

        for (int hash = 0; hash < counter2; hash++)
        {
            printf("#");
        }

        for (int space = 0; space < 2 ; space++)
        {
            printf(" ");
        }

        for (int hash2 = 0; hash2 < counter3; hash2++)
        {
            printf("#");
        }
        printf("\n");
        counter++;
        counter2++;
        counter3++;
    }
}