// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Declare the dictionary file to load and its size
FILE *dic_file = NULL;
unsigned int dic_size = 0;

// Hash table
node *table[N];

//  Make sure that the hash table starts with null node values
void clear_hash_table() {
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
    // TODO
    return false;
}

//--------------------------------------------------------------------------------------------------
// Hashes word to a number
//--------------------------------------------------------------------------------------------------
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
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
    if (dic_file == NULL) {
        return false;
    }

    // Insert each word of the dictionary into the hash table
    char word[LENGTH + 1];
    char c;
    int index = 0;

    while (fread(&c, sizeof(char), dic_file))
    {
        while (c != '\n')
        {
            word[index] = c;
            index++;
        }

        // Get hash value of the current word
        unsigned int word_hash = hash(word);


        // --- Initialize new node that will host the dictionary word ----------------------
        node *new_n = malloc(sizeof(node));
        // Return false if memory allocation failed
        if (new_n == NULL)
        {
            return false;
        }
        new_n->word = word;
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
            // Make sure memory is actually freed, else return false
            if (table[i] != NULL)
            {
                return false;
            }
            // Reassign table[i] to the next node
            table[i] = tmp;
        }
    }
    return true;
}
