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

//--------------------------------------------------------------------------------------------------
// Loads dictionary into memory, returning true if successful, else false
//--------------------------------------------------------------------------------------------------
bool load(const char *dictionary)
{
    // Make sure we start with an empty hash table
    clear_hash_table();

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

        // Initialize new node that will host the dictionary word
        node *new_n = malloc(sizeof(node));
        new_n->word = word;
        new_n->next = NULL;

        // Insert the word node in the hash table at the beginning of the chain (more performant)
        if (table[word_hash] == NULL)
        {
            table[word_hash] = new_n;
        }
        else
        {
            new_n->next = table[word_hash];
            table[word_hash] = new_n;
        }
        // Prepare for next word, reset index to 0
        index = 0;
    }
    // Close file when the whole dictionary has been loaded
    fclose(dic_file);
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


        return (dic_file != NULL) ? false : true;
    }
    return true;
}
