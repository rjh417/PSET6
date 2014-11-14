/****************************************************************************
 * dictionary.h
 *
 * Robert Hill
 * Computer Science 50
 * Problem Set 6
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// define hash table size 
#define HASHTABLE_SIZE 65536

/**
* Struct node definintion
*/
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

unsigned int hash(char* string);

/**
 * Hash function prototype
 */
//unsigned int hash(char* needs_hashing);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H
