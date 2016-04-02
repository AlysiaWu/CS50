/**
 * mario.c
 * problem set 1
 * CS50
 * Andrew Davies
 *
 */
 
#include <stdio.h>
#include <cs50.h>
 
int main(void)
{   
    // obtains a legit height from user
    int height;
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height > 23 || height < 0);
      
    // 2 for loops inside a for loop
    // big loop for the rows
    // inside the rows: one for the spaces, another for the #'s
    for (int row = 1; row <= height; row += 1)
    {
        for (int spaceloop = 1; spaceloop <= height - row; spaceloop += 1)
        {
            printf(" ");
        }
        for (int hashloop = 1; hashloop <= row + 1; hashloop += 1) 
        {
            printf("#");
        }
        printf("\n");
    }
}
