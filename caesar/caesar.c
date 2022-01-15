#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    //Intitalize Variables
    int key = 0;
    //Too many command arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //Validate command-line argument
    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
            else
            {
                key = atoi(argv[1]); //Convert key from string to int

            }
        }
    }

    //Asking for original text
    string text = get_string("plaintext: ");

    //Intializing variables
    string ciphertext;
    int c = 0;
    int input = 0;
    int ci = 0;
    int output = 0;


    //Encoding and printing ciphertext
    printf("ciphertext: ");

    //Iterates through each character in text and applies the key to convert to ciphertext
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                input = text[i] - 65;
                ci = (input + key) % 26;
                output = ci + 65;
                printf("%c", output);
            }
            if (islower(text[i]))
            {
                input = text[i] - 97;
                ci = (input + key) % 26;
                output = ci + 97;
                printf("%c", output);
            }
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;
}