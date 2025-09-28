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
} node;

// Choose number of buckets in hash table
const unsigned int N = 20000;

// Declare the dictionary file to load and its size
FILE *dic_file = NULL;
unsigned int dic_size = 0;

// Hash table
node *table[N];

// Hash structure
int table_structure[N];

//  Function to make sure that the hash table starts with null node values
void clear_hash_table()
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
}

//--------------------------------------------------------------------------------------------------
// Returns true if word is in dictionary, else false
//--------------------------------------------------------------------------------------------------
bool check(const char *word)
{
    // Convert word to lower case
    char lower_word[LENGTH + 1];
    for (int i = 0; i < strlen(word); i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[strlen(word)] = '\0';

    // Compute hash value of the word to check
    int hash_value = hash(lower_word);

    // Define traversal node and initialize it to the table pointer corresponding to the hash value
    node *n = table[hash_value];

    // Loop on each node of the linked list and return true if it's found
    while (n != NULL)
    {
        if (strcmp(n->word, lower_word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    // If the word is not found, return false
    return false;
}

// To be enhanced ----------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
// Hashes word to a number
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
unsigned int hash(const char *word)
{
    unsigned int result = 0;

    for (int i = 0; i < strlen(word); i++)
    {

        result = result * 131 + word[i];
        // result = (result << 5) ^ (result >> 27) ^ word[i];
    }
    return result % N;
}

// Done
//--------------------------------------------------------------------------------------------------
// Loads dictionary into memory, returning true if successful, else false
//--------------------------------------------------------------------------------------------------
bool load(const char *dictionary)
{
    // Make sure we start with an empty hash table and a dictionary size equal to 0
    clear_hash_table();
    dic_size = 0;

    // Define the variable to count the number of words load in the hash table
    unsigned int word_counter = 0;

    // Open dictionary into dic file
    dic_file = fopen(dictionary, "r");
    if (dic_file == NULL)
    {
        return false;
    }

    // Insert each word of the dictionary into the hash table
    char word[LENGTH + 1];
    char c;
    int index = 0;

    while (fread(&c, sizeof(char), 1, dic_file))
    {

        if (c != '\n')
        {
            word[index] = c;
            index++;
            continue;
        }
        // Add the nul character to indicate the end of the word
        word[index] = '\0';

        // Get hash value of the current word
        unsigned int word_hash = hash(word);
        table_structure[hash(word)]++;

        // --- Initialize new node that will host the dictionary word ----------------------
        node *new_n = malloc(sizeof(node));
        // Return false if memory allocation failed
        if (new_n == NULL)
        {
            return false;
        }
        strcpy(new_n->word, word);
        new_n->next = NULL;

        // --- Insert the word node in the hash table at the beginning of the chain -------------
        if (table[word_hash] == NULL)
        {
            table[word_hash] = new_n;
        }
        else
        {
            new_n->next = table[word_hash];
            table[word_hash] = new_n;
        }
        // Prepare for next word, increment size and reset index to 0
        word_counter++;
        index = 0;
    }
    // Close file when the whole dictionary has been loaded and update dictionary size
    fclose(dic_file);
    dic_size = word_counter;

    /* Debug print table structure
    for (int i = 0; i < N; i++)
    {
        printf("%i\n", table_structure[i]);
    }
    */

    // Return true
    return true;
}

// Done
//--------------------------------------------------------------------------------------------------
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
//--------------------------------------------------------------------------------------------------
unsigned int size(void)
{
    return dic_size;
}

// Done
//--------------------------------------------------------------------------------------------------
// Unloads dictionary from memory, returning true if successful, else false
//--------------------------------------------------------------------------------------------------
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp = NULL;
        while (table[i] != NULL)
        {
            // Set temporary pointer to the next node address in the chain
            tmp = table[i]->next;
            // Free the node memory
            free(table[i]);
            table[i] = NULL;
            // Reassign table[i] to the next node
            table[i] = tmp;
        }
        // Make sure memory is actually freed, else return false
        if (table[i] != NULL)
        {
            return false;
        }
    }
    return true;
}
