#include <stdio.h>
#include <cs50.h>

int get_height(void);
int calculate_spaces(int height);
int calculate_hashes(int n);
void print_pyramid(int h);

int main(void)
{
    int h = get_height();
    print_pyramid(h);
    
}

int get_height(void)
{
    int h;
    // Prompt user for height
    do
    {
        h = get_int("Height: ");
    } while (h < 1 || h > 8);
    return h;
}

int calculate_spaces(int height)
{
    // Calculate spaces needed
    int space = height - 1;
    return space;
}

int calculate_hashes(int n)
{
    // Calculate hashes needed
    int hash = n;
    return hash;
}

void print_pyramid(int height)
{
    int min = 1;
    int max = height;

    for (int i = 0; i < height; i++)
    {
        // Calculate Spaces and Hashes
        int s = calculate_spaces(max);
        int h = calculate_hashes(min);

        // Print Tower

        // Print Spaces
        for (int j = 0; j < s; j++)
        {
            printf(" ");
        }
        // Print left hashes
        for (int k = 0; k < h; k++)
        {
            printf("#");
        }
        // Print Gap
        printf("  ");
        // Print right hashes
        for (int k = 0; k < h; k++)
        {
            printf("#");
        }

        printf("\n");
        min++;
        max--;
    }
}