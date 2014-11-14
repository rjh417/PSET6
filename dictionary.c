/****************************************************************************
 * Robert Hill
 * dictionary.c
 * 
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// create hashtable
node* hashtable[HASHTABLE_SIZE];

// declare and initialize global variable to count dictionary words
unsigned int word_count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // create array for lowercase copy of word
    char lowercase[strlen(word) + 1];
          
    // declare and initialize variable for length of dictionary word
    int length = strlen(word);
    
    // interate through word and convert to lowercase copy
    for (int i = 0; i < length + 1; i++)
    {
        lowercase[i] = tolower(word[i]);
    }
    
    // append null character to indicate end of the word
    lowercase[length] = '\0';
    
    // hash word 
    unsigned int hashvalue = hash(lowercase);
    
    // no node attached to array pointer
    if (hashtable[hashvalue] == NULL)
    {
        return false;
    }
    
    // create pointer to traverse the linked-lists
    node* crawler = hashtable[hashvalue];
    
    // if hash index points to node, compare word to the node's word
    while (crawler != NULL)
    {
        if (strcmp(lowercase, crawler->word) == 0)
        {
            return true;
        }
        
        // if words don't match set pointer to next
        crawler = crawler->next;
                    
    }
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // declare array to store the dictionary word 
    char word[LENGTH + 1];
    
    // declare and initialize hashtable index
    int hashvalue = 0;
    
    // open dictionary 
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        // if not able to open dictionary, return false
        return false;
    }
    
    // read in dictionary words
    while (fscanf(fp, "%s ", word) == 1)
    {  
        // create node and check for NULL indicating no memory available
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
             return false;
        }
        
        // insert dictionary word into the new node
        strcpy(new_node->word, word);
                                            
        // hash the word
        hashvalue = hash(word);
  
        // if head points to null, point head to new node and new node to null
        if (hashtable[hashvalue] == NULL)
        {
            // set head pointer to point to new node
            hashtable[hashvalue] = new_node;
            
            // set new node to point to NULL indicating end of list
            new_node->next = NULL;
        }
        
        // insert new node at the beginning of the linked list        
        else 
        {
            // set new node pointer to point first node in list
            new_node->next = hashtable[hashvalue];
            
            // set array pointer to point to new node 
            hashtable[hashvalue] = new_node;
        }
   
        // update counter
        word_count++;
    }  
    
    // close dictionary file
    fclose(fp);
 
    // all's well    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // Return number of words in dictionary
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // declare and initialize hashtable index variable
    int index = 0;
    
    // iterate through hashtable
    //while (index < HASHTABLE_SIZE)
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
    
    // if no nodes attached, go to next hashtable index
    if (hashtable[index] == NULL)
    {
        index++;
    }
    
    // traverse linked list and free all nodes
    else
    {
        while(hashtable[index]!= NULL)
        {
            node* crawler = hashtable[index];
            hashtable[index] = crawler->next;
            free(crawler);
        }
        
        // increment index
        index++;
    }
    }
    
    // all's well
    return true;
}
/**
 * Hash function. This hash function was provided by Brenda's husband and
 * was found on Reddit at http://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn
 */

unsigned int hash(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}
