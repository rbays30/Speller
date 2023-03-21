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

//Bucket length is the max value of a letter * the max length of the array * length per hash funciton
const unsigned long int N = 26 * LENGTH * 26;

//Initialize other utility values
long int size_lib = 0;
long int free_count = 0;
int match = 0;

// Hash table
node *table[N];

//Prototypes

bool create_node(int value);
void free_node(node *ptr);
void clear_array(char *word_array);
void copy_word(char *recorded_word, node *table);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Grab the hash value of the word to be checked
    int sort_num_text = hash(word);

    //Initialize pointer to search through table
    node *table_ptr = NULL;

    //If the bucket hasn't been initialized, return false
    if (table[sort_num_text] == NULL)
    {
        return false;
    }

    //Set the pointer to the bucket hashed from the word
    table_ptr = table[sort_num_text];

    //Infinite loop that stops when the next pointer is null or the word matches
    while (true)
    {
        //Variable to determine match
        match = strcasecmp(table_ptr->word, word);

        //Matching word
        if (match == 0)
        {
            return true;
        }

        //Non matching word
        if (table_ptr->next == NULL)
        {
            return false;
        }

        //If neither of these scenarios happened, check the next value
        table_ptr = table_ptr->next;
    }

    //If the word is not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{


    //Initialize variables
    long int sum = 0;
    int length = strlen(word);
    unsigned int hash_value = 0;
    int value = 0;

    //Loop through the word, summing ASCII values of word as long as there is no apostrophes
    for (int i = 0; i < length; i++)
    {
        value = (int)(toupper(word[i]) - 'A');

        //Make sure no apostrophes are included
        if (value > 0)
        {
            sum += value;
        }
    }

    //Hash value is the sum of ASCII values times the length of the word
    hash_value = sum * length;

    //Return value
    return hash_value;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    //Open File
    FILE *input = fopen(dictionary, "r");

    //If file open fails, exit and return false
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

    //Initialize Variables
    int sort_num = 0;
    char current_word[LENGTH + 1];
    char last_char = '\0';
    int count = 0;
    size_t read_value = 1;


    //Initialize pointer to control stack
    char *ptr_current = NULL;
    ptr_current = &current_word[0];

    //Function to change array to all '\0'
    clear_array(ptr_current);

    //Obtain a character
    do
    {
        //Read the next character
        read_value = fread(buffer, sizeof(char), 1, input);

        //if the last recorded character is a new line, must be a new word that needs a new node
        if (last_char == '\n')
        {
            //Load the current word into the hash function
            sort_num = hash(current_word);

            //Creates a new node to place the word
            bool success = create_node(sort_num);

            //If node creation failed, return false to show error
            if (!success)
            {
                printf("Out of Memory for new pointer.\n");
                return false;
            }

            //Load the current word into a node
            copy_word(ptr_current, table[sort_num]);

            //Variable to track size of library
            size_lib += 1;

            //Prepare for new word
            clear_array(ptr_current);
            count = 0;
        }

        //If buffer is not a new line, print the value to the array
        if (*buffer != '\n')
        {
            current_word[count] = *buffer;
        }

        //Prepare for next loop
        last_char = *buffer;
        count += 1;

    }
    while (read_value);

    //Close file
    fclose(input);

    //Free buffer
    free(buffer);

    return true;
}

//Creates a node based on the given value/bucket
bool create_node(int value)
{
    //Allocate memory for a new node
    node *new_node = malloc(sizeof(node));

    //Check to make sure node creation was successful, otherwise return false
    if (new_node == NULL)
    {
        return 0;
    }

    //Ensure clean NODE with starting values of null for next and all '\0' for word
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
    return size_lib;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //Initialize a pointer to point at different nodes to free them
    node *ptr = NULL;

    //For each bucket, recursively free the parent, and then free the child
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            ptr = table[i];
            free_node(ptr);
        }
    }

    //Check to make sure every node was freed
    if (free_count == size_lib)
    {
        return true;
    }

    //If not all nodes were freed, return false
    return false;
}


//Function to free the given pointer
void free_node(node *ptr)
{
    if (ptr->next != NULL)
    {
        free_node(ptr->next);
    }

    free(ptr);

    //Track how many nodes were freed
    free_count += 1;

}

//Function to fill an array with '\0'
void clear_array(char *word_array)
{
    for (int i = 0; i < LENGTH; i++)
    {
        word_array[i] = '\0';
    }
}

//Function to copy the word stored in memory to a node
void copy_word(char *recorded_word, node *table_value)
{
    for (int i = 0; i < LENGTH; i++)
    {
        if (recorded_word[i] == '\0')
        {
            table_value->word[i] = '\0';
            return;
        }

        table_value->word[i] = recorded_word[i];
    }

}