#include <stdio.h>
#include <cs50.h>
#include <string.h>

string s;
int i;
int counter;

int main(void)
{
      s = "Ahoj ako sa mas.";

     for (i = 0; i < strlen(s); i++)
     {
         counter++;
         printf("%c",s[i]);
         
     }
     printf("\n Count is: %i\n",counter);
}