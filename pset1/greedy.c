/**
 * greedy.c
 * CS50 pset1
 *
 * Andrew Davies
 * 22/09/15
 *
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h> // need roundf function

int main(void)
{
    // get non-negative input from user
    printf("O hai! How much change is owed?\n");
    float change_owed = GetFloat();
    while (change_owed < 0)
    {
        printf("How much change is owed?\n");
        change_owed = GetFloat();
    } 
    
    // convert float to int so can calc accurately
    // roundf avoids truncation errors
    int cents_owed = roundf(change_owed * 100);
                                                
    // declare 'coin' constants
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    
    // initialise variables
    int cents_remain = cents_owed;
    int coins_given = 0; 
    int coin;
    
    for (int i = 1; i <= 4; i += 1)
    {
        // switch more elegant than repeated if/else
        switch (i)
        {
            case 1:
                coin = quarter;
                break;
                
            case 2:
                coin = dime;          
                break;
                
            case 3:
                coin = nickel;
                break;
                
            case 4:
                coin = penny;
                break;
        }
        
        // give the change
        coins_given += cents_remain / coin;
        cents_remain = cents_remain % coin;   
        
        // to avoid unnecessary loops
        if (cents_remain == 0)
        {
            break;    
        }
    }
    
    printf("%i\n", coins_given);
}
