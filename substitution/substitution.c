#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, string argv[])
{
    //Intitalize Variables
    int c = 0;
    string key = argv[1];
    //Too many command arguments
    if(argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //Validate command-line argument
    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]))
            {
                c++;
                if(argv[1][i] == argv[1][i+1])
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }

            else
            {
                printf("Key must contain only alphabetic characters.\n");
                return 1;
            }
        }
        if (c < 26)
        {
            printf("Key must contain 26 characters.");
            return 1;
        }
    }

    //Asking for original text
    string text = get_string("plaintext: ");
    printf("text: %s\n", text);
    
    int difference[26];
    
    for (int i = 0; i< 26; i++)
    {
        difference[i]  = (key[i] - UPPER[i]);
        printf("%i\n", difference[i]);
    }
    
    //string ciphertext = text;
    
    /*
    if (isalpha(ciphertext))
    {
        for (int i = 0, n = strlen(ciphertext); i < n; i++)
        {
            ciphertext += (key[i] - UPPER[i]);
        }
    }
    */
    //printf("ciphertext: %s \n", ciphertext);
    return 0;
}