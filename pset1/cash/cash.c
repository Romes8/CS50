#include <stdio.h>
#include <cs50.h>
#include <math.h>

float cents;
int num, counter;
int change = 0;

int main(void)
{
    do  // checks for valid input
    {
        cents = get_float("What is your price : ");
    }
    while (cents < 0.001);
    num = round(cents * 100);
    printf("Price: %i\n", num);
    do  // calculates
    {
        if (num >= 25)
        {
            num = num - 25;
            printf("Num 25 je: %i\n", num);
            counter++;
        }
        else if (num >= 10)
        {
            num = num - 10;
            printf("Num 10 je: %i\n", num);
            counter++;
        }
        else if (num >= 5)
        {
            num = num - 5;
            printf("Num 5 je: %i\n", num);
            counter++;
        }
        else if (num >= 1)
        {
            num = num - 1;
            printf("Num 1 je: %i\n", num);
            counter++;
        }
    }
    while (num != 0);
    // result
    printf("The end.\n");
    printf("Counter is: %i\n", counter);
}