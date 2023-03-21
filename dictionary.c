// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned long int N = 26 * LENGTH * 26;
double size_lib = 0;
double free_count = 0;
int match = 0;
int collision = 0;


// Hash table
node *table[N];

//Prototypes

bool create_node(int value);
void free_node(node * ptr);
void clear_array(char * word_array);
void copy_word(char * recorded_word, node * table);


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
        match = strcasecmp(table_ptr->word, word);
        if (match == 0)
        {
            return true;
        }

        if(table_ptr->next == NULL)
        {
            collision += 1;
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

    //Sum ASCII values of string

    long int sum = 0;
    int length = strlen(word);
    unsigned int hash_value = 0;

    int value = 0;

    for (int i = 0; i < length; i++)
    {
        value = (int)(toupper(word[i]) - 'A');

        if (value > 0)
        {
            sum += value;
        }
    }

    hash_value = sum * length;

    return hash_value;
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
    char * ptr_current = NULL;
    ptr_current = &current_word[0];

    clear_array(ptr_current);
    char last_char = '\0';
    int count = 0;
    size_t read_value = 1;

    //Obtain a character
    do
    {

        read_value = fread(buffer, sizeof(char), 1, input);

        //if the last character is a first letter
        if (last_char == '\n')
        {
            //Load the current word into the hash function
            sort_num = hash(current_word);

            //Creates a new node to place the word
            bool success = create_node(sort_num);
            if(!success)
            {
                printf("Out of Memory for new pointer.\n");
                return false;
            }

            //Load the current word into a node
            copy_word(ptr_current,table[sort_num]);
            size_lib += 1;


            //Prepare for new word
            clear_array(ptr_current);
            count = 0;
        }

        if(*buffer != '\n')
        {
            // printf("Buffer: %c\n", *buffer);
            current_word[count] = *buffer;
        }

        //Prepare for next loop
        last_char = *buffer;
        count += 1;

    } while(read_value);




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
        // printf("Collisions: %i\n", collision);

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

void clear_array(char * word_array)
{
    for (int i = 0; i < LENGTH; i++)
    {
        word_array[i] = '\0';
    }
}

void copy_word(char * recorded_word, node * table_value)
{
    for (int i = 0; i < LENGTH; i++)
    {
        if (recorded_word[i] == '\0')
        {
            table_value->word[i] = '\0';
            // printf("Word recorded as: %s \n", table_value->word);
            return;
        }

        table_value->word[i] = recorded_word[i];
    }

}