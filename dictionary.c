// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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
double size_lib = 0;
double free_count = 0;


// Hash table
node *table[N];

//Prototypes

bool create_node(int value);
void free_node(node * ptr);


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Grab the hash value of the word to be checked
    int sort_num_text = hash(word);

    //Initialize pointers to search through tables
    node * table_ptr = NULL;
    if (table[sort_num_text] == NULL)
    {
        return false;
    }

    table_ptr = table[sort_num_text];
    while(true)
    {
        bool match = strcasecmp(table_ptr->word, word);
        if (match == 0)
        {
            return true;
        }

        if(table_ptr->next == NULL)
        {
            return false;
        }

        table_ptr = table_ptr->next;
    }

    //If the word is not found

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
    int sort_num = 0;
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

    node * ptr = NULL;
    node * temp_node = NULL;


    //Obtain a character

    int count = 0;
    while (fread(buffer, sizeof(char), 1, input))
    {
        //if the last character is a first letter
        if (last_char == '\n')
        {
            sort_num = hash(buffer);
            size_lib += 1;

            //Creates a new node
            bool success = create_node(sort_num);
            if(!success)
            {
                printf("Out of Memory for new pointer.\n");
                return false;
            }

            count = 0;
        }

        if(*buffer != '\n')
        {
            table[sort_num]->word[count] = *buffer;
        }

        //Prepare for next loop
        last_char = *buffer;
        count += 1;
    }
    fclose(input);
    free(buffer);


    return true;
}

//Creates a node

bool create_node(int value)
{
    node * new_node = malloc(sizeof(node));
    if(new_node == NULL)
    {
         return 0;
    }

    //Ensure clean NODE
    for (int i = 0; i < LENGTH + 1; i++)
    {
        new_node->word[i] = '\0';
    }
    new_node->next = NULL;

    //Set next to current node in case of collisions, otherwise will be set to NULL
    new_node->next = table[value];

    //Set the current node to be equal to the new_node pointing to the new data
    table[value] = new_node;

    return 1;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_lib;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node * ptr = NULL;
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            ptr = table[i];
            free_node(ptr);
        }
    }

    if(free_count == size_lib)
    {
        return true;
    }

    return false;
}

void free_node(node * ptr)
{
    if (ptr->next != NULL)
    {
        free_node(ptr->next);
    }

    free(ptr);
    free_count += 1;

}