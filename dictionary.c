// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *input = fopen(dictionary,"r");
    if (input == NULL)
    {
        return 0;
    }

    //Initialize the buffer

    char *buffer = malloc(sizeof(char)*(LENGTH + 1));
    if (buffer == NULL)
    {
        return 0;
    }

    //Read dictionary into an array of word length

    while (fread(buffer, sizeof(char), 1, input))
    {
        printf("%s ", buffer);
    }


    //Could do as an array of LENGTH

    //Could reallocate memory as it goes
    //Could do a list



    //Write buffer to memory array

    //Close file

    //Free buffer


    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
