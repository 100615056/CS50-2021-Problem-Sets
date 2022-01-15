#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//Prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float calculate_index(int c, int w, int s);

int main(void)
{

    string t = get_string("Text: ");

    int c = count_letters(t);

    int w = count_words(t);

    int s = count_sentences(t);

    int index = round(calculate_index(c, w, s));

    //Print Grade Level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }

    if (index > 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }

}

int count_letters(string text)
{


    //Initalize Variables
    int count = 0;

    //Count the number of letters from the user's text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    //Initalize Variables
    int word = 0;

    //Count the number of words
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            word++;
        }
    }
    word = word + 1;
    return word;
}

int count_sentences(string text)
{
    //Initalize Variables
    int sentence = 0;

    //Count the number of sentences from the user's text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //Checking for . or ! or ? using ASCII
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentence++;
        }
    }
    return sentence;
}

float calculate_index(int c, int w, int s)
{
    //Calulate the L and S values for the Coleman-Liau index
    float L = (float) c / (float) w * 100.00;
    float S = (float) s / (float) w * 100.00;

    //Compute the index
    float index =  0.0588 * L - 0.296 * S - 15.8;
    return index;
}