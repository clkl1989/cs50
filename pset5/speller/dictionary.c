// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 4096; //needs to be updated with the # of buckets later (how to find size of hashtable?)

// Hash table
node *table[N];

// Variable for hash index
unsigned int hash_index;

// Variable for word count in dictionary
unsigned int word_count;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    hash_index = hash(word); // Hash word to find hash index on Hash Table

    //Access linked list @ the index on Hash Table (find hash index)
    node *tmp = table[hash_index];

    //Go through every element in the linked list attached to the hash index
    while (tmp != NULL)
    {
        //check if the word matches
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }

        tmp = tmp->next; //move to next node
    }

    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Using hash function djb2 by Dan Bernstein.
    unsigned int hash = 5381;
    int c;

    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % N; //get the bucket
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    //1. open the dictionary file
    FILE *dict = fopen (dictionary, "r");

    if (dict == NULL)
    {
        printf("%p cannot be opened.\n", dict); //inform user that the dictionary file cannot be opened
        return false;
    }

    else
    {
        char word[LENGTH+1]; //creates a buffer for a word with 45 char (longest possible), already defined once at the top
    
        while (fscanf(dict,"%s", word) != EOF) //repeat until the end of the file
        {

            //allocate memory for a node pointer for each new word
            //create a new node for every word
            node *new_node = malloc(sizeof(node));
            // check if malloc fails
            if (new_node == NULL)
            {
                fclose(dict);
                printf("Memory allocation failed\n");
                return false;
            }
            // Copy word into node
            else
            {

                strcpy(new_node->word, word);

                //insert node into hash table (hash word and then insert node into the linked list of hash table)

                //hash word
                hash_index = hash(word);

                //insert node into one of the linked list in the hash table
                new_node->next = table[hash_index];

                // Set head to new pointer
                table[hash_index] = new_node;

                // Increment word count
                word_count++;

            }

        }

        fclose(dict);
        return true;

    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count == 0)
    {
         return 0;
    }
    
    else
    {
        return word_count;
    }
    
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++) //starting from the first bucket to the last
    {
        node *cursor = table[i]; //point cursor to the bucket
        
        // If cursor is not pointing to NULL, free the content in the location
        while (cursor != NULL)
        {
            // Create temp 
            node *tmp = cursor;
            // Move cursor to next node
            cursor = cursor->next;
            // Free up temp
            free(tmp);
        }
        // we have reached the of the hash table and if cursor is NULL
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
