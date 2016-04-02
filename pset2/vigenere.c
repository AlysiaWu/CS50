/**
 * vigenere.c
 * cs50 pset2
 * andrew davies 06/10/15
 *
 * encrypts text that the user enters
 *
 */
 
#include <stdio.h>  // printf
#include <cs50.h>   // GetString
#include <string.h> // strlen
#include <ctype.h>  // isalpha

int main(int argc, string argv[])
{
    // return error if anything other than
    // 2 command line arguments entered
    if (argc != 2)
    {
        printf("error: must enter one command line arg\n");
        return 1;
    } 
    
    // return error if argv contains a non-alpha char
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("non-letter char entered at i = %i\n", i);
            return 1;
        }
    }
    
    // get message from user
    string InMessage = GetString();
    
    // for each char, if alphabetical char encrypt,
    // else leave it
    string OutMessage = InMessage;
    int k;
    for (int i = 0, j = 0, n = strlen(InMessage); i < n; i++)
    {
        if (isalpha(InMessage[i]))
        {
            k = argv[1][j % strlen(argv[1])];
            if (isupper(k))
            {
                k -= 65;
            } 
            else
            {
                k -= 97;
                }
            
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
            j++;
        }
    }
           
    // print encrypted message
    printf("%s\n", OutMessage);
    return 0;
}
