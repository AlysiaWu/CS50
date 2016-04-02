/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

// binary search (pset3 - 'search')
bool binsearch(int value, int values[], int upper, int lower)
{
    int length = upper - lower + 1;
    int middle = (lower + upper) / 2;
    
    while (length > 0)
    {
        if (values[middle] == value)
        {
            return true;
        }      
        else if (values[middle] > value)
        {
            // search left
            upper = middle - 1;
            return binsearch(value, values, upper, lower);
        }
        else if (values[middle] < value)
        {
            // search right
            lower = middle + 1;
            return binsearch(value, values, upper, lower);
        }
    } 
    return false;   
}

bool search(int value, int values[], int n)
{
    // binary search (pset3 - 'search')
    int lower = 0;
    int upper = n - 1;
    return binsearch(value, values, upper, lower);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // bubble sort (pset3 - 'sort')
    
    for (int i = 0; i < (n - 1); i++)
    {
        int swapcount = 0;
        for (int j = 0; j < (n - 1 - i); j++)
        {
            if (values[j] > values[j + 1])
            {
                // swap
                int temp = values[j + 1];
                values[j + 1] = values[j];
                values[j] = temp;
                swapcount++;
            }
            
        }
        if (swapcount == 0)
        {
            break;
        }
    }
    return;
}
