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

// Declare the dictionary file to load
FILE *dic_file = NULL;

// Hash table
node *table[N];

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

//--------------------------------------------------------------------------------------------------
// Loads dictionary into memory, returning true if successful, else false
//--------------------------------------------------------------------------------------------------
bool load(const char *dictionary)
{
    // Open dictionary into dic file
    dic_file = fopen(dictionary, "r");
    if (dic_file == NULL) {
        return false;
    }

    // Insert each word of the dictionary into the hash table
    char c;
    while ()






}

//--------------------------------------------------------------------------------------------------
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
//--------------------------------------------------------------------------------------------------
unsigned int size(void)
{
    // TODO
    return 0;
}

//--------------------------------------------------------------------------------------------------
// Unloads dictionary from memory, returning true if successful, else false
//--------------------------------------------------------------------------------------------------
bool unload(void)
{
    if (dic_file != NULL)
    {
        fclose(dic_file);
        return (dic_file != NULL) ? false : true;
    }
    return true;
}
