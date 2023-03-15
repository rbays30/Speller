// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//Prototypes

bool create_node(node * current_node);

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
    printf("Hi");


    FILE *input = fopen(dictionary,"r");
    if (input == NULL)
    {
        return 0;
    }

    //Initialize the buffer
    char *buffer = malloc(sizeof(char));
    if (buffer == NULL)
    {
        return 0;
    }

    //Initialize the hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char current_word[LENGTH + 1];
    char last_char = '\n';

    int sort_num = atoi(buffer);
    node * ptr = NULL;
    node * temp_node = NULL;


    //Obtain a character

    int count = 0;
    while (fread(buffer, sizeof(char), 1, input))
    {
        sort_num = atoi(buffer);
        //if the last character is a first letter
        if (last_char == 'n')
        {
            //Creates a new node
            bool success = create_node(table[sort_num]);
            if(!success)
            {
                printf("Out of Memory for new pointer.\n");
                return 1;
            }

            count = 0;
        }

        table[sort_num]->word[count] = *buffer;

        //Prepare for next loop
        last_char = *buffer;
        count += 1;
    }

    //Check to make sure words were copied
    for (int i = 0; i < 5; i++)
    {
        node *printer = NULL;
        printer = table[20];
        printf("Word is: %s\n", printer->word);
        i += 1;

    }


    //Check and see if there's a pointer for that letter

    //If there's not, create one

    //If there is, create a "next" pointer in that pointer and follow the pointer to next


    return false;
}

//Creates a node

bool create_node(node * current_node)
{
    printf("Hi There\n");
    node * new_node = malloc(sizeof(node));
    if(new_node == NULL)
    {
         return 0;
    }

    //Ensure clean NODE
    //memset(new_node->word,NUL,[LENGTH + 1]);
    new_node->next = NULL;

    //Set next to current node in case of collisions, otherwise will be set to NULL
    new_node->next = current_node;

    //Set the current node to be equal to the new_node pointing to the new data
    current_node = new_node;

    return 1;
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
