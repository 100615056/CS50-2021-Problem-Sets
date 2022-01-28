#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Initialize variables
    int start;
    int end;
    int year = 0;

    // Prompt for start size
    do
    {
        start = get_int("Start size: ");
    } 
    while (start < 9);

    // Prompt for end size
    do
    {
        end = get_int("End size: ");
    } 
    while (end < start);
    
    // Initializing population
    int n = start;
    // Calculate number of years until we reach threshold
    while (n < end)
    {
        n = n + (n / 3) - (n / 4);
        year++;
    }
    // Print number of years
    printf("Years: %i\n", year);
}