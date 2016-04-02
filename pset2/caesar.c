/**
 * caesar.c
 * cs50 pset2
 * andrew davies 05/10/15
 *
 * encrypts text that the user enters
 *
 */
 
#include <stdio.h>  // printf
#include <cs50.h>   // GetString
#include <stdlib.h> // atoi
#include <string.h> // strlen
#include <ctype.h>  // isalpha

int main(int argc, string argv[])
{
    // return error if anything other than
    // 2 command line arguments entered
    if (argc != 2)
    {
        printf("oi!\n");
        return 1;
    } 
    
    // convert string in CL to int k
    int k = atoi(argv[1]);
    
    // make sure k is positive
    if (k < 1)
    {   
        printf("oi!\n");
        return 1;
    }
    
    // get message from user
    string InMessage = GetString();
    
    // for each char, if alphabetical char encrypt,
    // else leave it
    string OutMessage = InMessage;
    for (int i = 0, n = strlen(InMessage); i < n; i++)
    {
        if (isalpha(InMessage[i]))
        {
            if (isupper(InMessage[i]))
            {
                // convert from ascii to alphabet index
                InMessage[i] -= 65;              
                OutMessage[i] = (InMessage[i] + k) % 26;
                // convert back to ascii
                OutMessage[i] += 65;
            }
            else
            {
                InMessage[i] -= 97;
                OutMessage[i] = (InMessage[i] + k) % 26;
                OutMessage[i] += 97;
            }
        }
    }
       
    // print encrypted message
    printf("%s\n", OutMessage);
    return 0;
}
