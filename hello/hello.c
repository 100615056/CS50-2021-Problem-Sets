#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks user for name and prints output
    string name = get_string("What is your name?");
    printf("hello, %s\n", name);
}