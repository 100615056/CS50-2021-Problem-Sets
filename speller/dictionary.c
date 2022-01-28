// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table - 26 * 26
const unsigned int N = 676;

// Hash table
node *table[N];

// Global variable to count the number of words
int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Take length of string (word) and add one to account for \0 - end of string
    int len = strlen(word);
    //Create new word
    char text_word[len + 1];

    // Case-insensitive - thus convert everything to lowercase
    for (int i = 0; i < (len + 1); i++)
    {
        text_word[i] = tolower(word[i]);
    }

    // Hash word to obtain hash value
    int index = hash(text_word);

    // Point cursor to front
    node *cursor = table[index];

    // Traverse through list and compare word with dictionary words, until cursor is NULL (end of linked list)
    while (cursor != NULL)
    {
        if (strcasecmp(text_word, cursor->word) == 0)
        {
            return true;
            
        }
        // Move cursor along linked list
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Credits to Engineer Man for the Hash Function (https://www.youtube.com/watch?v=wg8hZxMRwcw&list=WL&index=13)

    // Variable Initialization
    unsigned long int hash = 0;
    unsigned int i = 0;
    unsigned int word_length = strlen(word);

    // do several rounds of multiplication
    for (; i < word_length; ++i) 
    {
        hash = hash * 37 + word[i];
    }

    // make sure hash value is 0 <= hash < N
    hash = hash % N;

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file and read words from file
    FILE *file = fopen(dictionary, "r");

    // Error check
    if (file == NULL)
    {
        return 1;
    }

    // Initialize dictionary word
    char dict_word[LENGTH + 1];

    // Scan each word until reached the end
    while (fscanf(file, "%s", dict_word) != EOF)
    {
        // Create node
        node *n = malloc(sizeof(node));

        // Error check
        if (n == NULL)
        {
            return 1;
        }

        // Copying word to node - current address is NULL - to avoid memory leakage
        strcpy(n->word, dict_word);
        n->next = NULL;

        // Hash word to receive hash value
        int index = hash(n->word);

        // Start of linked list
        if (table[index] == NULL)
        {
            table[index] = n;
            count++;
        }

        else
        {
            // Set new element to be in front and then reset the first element to be the new node
            n->next = table[index];
            table[index] = n;
            count++;
        }
    }

    // Close file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return the global count variable -  incremented in the load function
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // Create node to point to nodes
        node *cursor = table[i];
        while (cursor != NULL)
        {
            // Create temporary node
            node *tmp = cursor;
            // Move cursor ahead of temporary node
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
