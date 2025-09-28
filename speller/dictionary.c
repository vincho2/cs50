// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Define ALPHABET
const unsigned int ALPHABET = 26;

// Represents a node in the tree
typedef struct node {
    struct node *child[ALPHABET + 1];
    bool is_end_of_word;
} node;



// Declare the dictionary file to load and its size
FILE *dic_file = NULL;
unsigned int dic_size = 0;

// Trie
node *trie = NULL;

//--------------------------------------------------------------------------------------------------
// Returns true if word is in dictionary, else false
//--------------------------------------------------------------------------------------------------
bool check(const char *word) {
    // Convert word to lower case
    char lower_word[LENGTH];
    for (int i = 0; i < strlen(word); i++) {
        lower_word[i] = tolower(word[i]);
    }

    // Define traversal node and initialize it to the table pointer corresponding to the hash value
    node *traversal = trie;
    unsigned int c_index;

    // Follow the trie to check whether the word is present or not
    for (int i = 0; i < strlen(word); i++)
    {
        // Compute character index
        c_index = (word[i] == '\'') ?  ALPHABET : word[i] - 'a';

        // If the path does not exist in the trie, then return false
        if (traversal == NULL || traversal->child[c_index] == NULL)
        {
            return false;
        }
        // Else follow the next node in the trie
        traversal = traversal->child[c_index];
    }
    // At the last node, end of word shoud be true
    if (traversal->is_end_of_word == true)
    {
        return true;
    }
    // If the word is not found, return false
    return false;
}

//--------------------------------------------------------------------------------------------------
// Loads dictionary into memory, returning true if successful, else false
//--------------------------------------------------------------------------------------------------
bool load(const char *dictionary) {

    // Initialize dictionary size and word counter to 0
    dic_size = 0;
    unsigned int word_counter = 0;

    // Open dictionary into dictionary file
    dic_file = fopen(dictionary, "r");
    if (dic_file == NULL) {
        return false;
    }

    // Initialize Trie by allocating memory and initialize the 1st node
    trie = malloc(sizeof(node));
    for (int i = 0; i < ALPHABET + 1; i++) {
        trie->child[i] = NULL;
    }
    trie->is_end_of_word = false;

    // Insert each word of the dictionary into the trie
    char c;
    unsigned int c_index;
    
    // Initialize traversal pointer to trie
    node *traversal = trie;

    // Loop on each character of the dictionary
    while (fread(&c, sizeof(char), 1, dic_file)) {
        // While c is not a newline, go down to the tree and create new nodes when missing
        if (c != '\n') {

            // Compute character index
            c_index = (c == '\'') ?  ALPHABET : c - 'a';

            // Go down to the trie an create new node if not there
            if (traversal->child[c_index] == NULL) {
                traversal->child[c_index] = malloc(sizeof(node));
                for (int i = 0; i < ALPHABET + 1; i++) {
                    traversal->child[c_index]->child[i] = NULL;
                    traversal->child[c_index]->is_end_of_word = false;
                }
            }

            // Move traversal pointer 1 step down and move to next char
            traversal = traversal->child[c_index];
        }
        // When c is a newline, then set end of word flag to true and reset traversal to trie root
        else {
            word_counter++;
            traversal->is_end_of_word = true;
            traversal = trie;
        }
    }
    // Close file when the whole dictionary has been loaded and update dictionary size
    fclose(dic_file);
    dic_size = word_counter;

    // Return true
    return true;
}

//--------------------------------------------------------------------------------------------------
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
//--------------------------------------------------------------------------------------------------
unsigned int size(void) {
    return dic_size;
}

//--------------------------------------------------------------------------------------------------
// Free dictionary from memory, returning true if successful, else false
//--------------------------------------------------------------------------------------------------
bool free_trie(node *tmp) {
    if (tmp == NULL)
    {
        return false;
    }
    while (tmp != NULL) {        
        for (int i = 0; i < ALPHABET + 1; i++) {
            free_trie(tmp->child[i]);
            tmp->child[i] = NULL;
        }
    }
    free(tmp);
    tmp = NULL;
    return true;
} 

//--------------------------------------------------------------------------------------------------
// Unloads dictionary from memory, returning true if successful, else false
//--------------------------------------------------------------------------------------------------
bool unload(void) {
    return free_trie(trie);
}
