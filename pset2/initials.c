/**
 * initials.c
 * cs50 pset2
 * andrew davies 05/10/15
 *
 * prints capitalised initials of the user's name
 *
 */
 
#include <stdio.h>   // to use printf
#include <cs50.h>    // to use GetString
#include <ctype.h>   // to use toupper
# include <string.h> // to use strlen

int main(void)
{
    string name = GetString();
    // print first letter in uppercase
    printf("%c", toupper(name[0]));
    
    // loop through subsequent letters
    // and if a char has a space before it,
    // print it
    for (int i = 1, n = strlen(name); i < n; i++)
    {
        if (name[i - 1] == ' ')
        {
            printf("%c", toupper(name[i]));
        }
    }
    printf("\n");
}
