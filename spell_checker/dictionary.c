// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Function declaration to handle checking if two char *words match, returns true or false boolean
bool words_match(const char *word_1, const char *word_2);

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table -> set each of the 26 nodes (0-25) to NULL
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer to hold an individual dictionary word at a time
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // printf("Letter '%c'. Bucket '%i'. Word '%s'\n", word[0], word[0]-'a', word); // => `Dictionary Word: alpha`
        // get the bucket number 0-25 for the current word
        int bucket = hash(word);

        // holds the current node in the hashtable's linked list (starting at 0)
        node *head_node = hashtable[bucket];

        // printf(" hashtable[%i] node mem location: %p\n", bucket, current_node);

        if (head_node == NULL)
        { // This is the first node
            // printf(" Node == NULL true. Setting first/head node of bucket %c|%i to %s.\n", word[0], word[0]-'a', word);

            head_node = malloc(sizeof(node));
            // malloc pointer test
            if (head_node == NULL) {
                fprintf(stderr, "Failure allocating memory for a new head node.");
                return 2;
            }
            // initialize the head node's next pointer as null
            head_node->next = NULL;

            // set the head node's member/field word
            for (int w = 0; w < sizeof(word); w++)
            {
                head_node->word[w] = word[w];
            }
            hashtable[bucket] = head_node;
            // printf("  Head node word set to %s. Hashtable[%i]: %s. %p|%p\n", head_node->word, bucket, hashtable[bucket]->word, head_node, hashtable[bucket]);
        }
        else
        { // this is NOT the first node
            // printf(" Node != NULL. Prepending new first/head node of bucket %c|%i to %s.\n", word[0], word[0]-'a', word);
            // create a new node
            node *new_node = malloc(sizeof(node));
            // malloc pointer test
            if (new_node == NULL) {
                fprintf(stderr, "Failure allocating memory for a new node.");
                return 2;
            }
            // Set the new node to point to the location of the previous head node
            new_node->next = head_node;

            // set the new_node's member/field word
            for (int w = 0; w < sizeof(word); w++)
            {
                new_node->word[w] = word[w];
            }

            // set the hashtable bucket to now point to the new prepended linked list node
            hashtable[bucket] = new_node;
            // printf("  Hashtable[%i] now points to word: '%s'. %p|%p\n", bucket, hashtable[bucket]->word, new_node, hashtable[bucket]);
        }
    }
    // printf("Dictionary EOF reached.\n\n");

    // Close dictionary
    fclose(file);

    // Runs through the hashtable and each node in the linked list, printing them on a line. Test to ensure load worked correctly
    // printf("\nDictionary: ");
    // // for each bucket/letter of the alphabet
    // for (int j = 0; j < N; j++)
    // {
    //     // if there is a node element at that location with a word member/field
    //     if (hashtable[j] && *hashtable[j]->word)
    //     {
    //         // get a pointer to the current node in the current bucket of the hashtable
    //         node *current_node = hashtable[j];
    //         printf("%s, ", current_node->word);
    //         // while the current node's next pointer is also not null (first word already counted above)
    //         while (current_node->next != NULL)
    //         {
    //             // there is another node in the linked list, advance to it and check again
    //             current_node = current_node->next;
    //             printf("%s, ", current_node->word);
    //         }// now we have found the last linked list node.
    //     }
    //     else
    //     {
    //         printf("%c|%i no node, ", j + 'a', j);
    //     }
    // }
    // printf("\n");

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    // for each bucket/letter of the alphabet
    for (int j = 0; j < N; j++)
    {
        // if there is a node element at that location with a word member/field
        if (hashtable[j] && *hashtable[j]->word)
        {
            // increase the count (count the first word here)
            count++;
            // get a pointer to the current node in the current bucket of the hashtable
            node *current_node = hashtable[j];
            // while the current node's next pointer is also not null (first word already counted above)
            while (current_node->next != NULL)
            {
                // there is another node in the linked list, advance to it and check again
                count++;
                current_node = current_node->next;
            }// now we have found the last linked list node.
        }
    }
    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // hash the first character to find which bucket 0-25 the word would be in
    int bucket = hash(word);

    // get the first linked list node in the hashtable at that bucket
    node *dictionary_ll_node = hashtable[bucket];

    if (dictionary_ll_node == NULL)
    {
        // printf("Word '%s'. Hashtable bucket %i has no dictionary words to check against.\n", word, bucket);
        return false;
    } // the current node is NOT null going forward

    // while there are more nodes to check...
    while (dictionary_ll_node != NULL)
    {
        // printf("\nChecking node in bucket %i.\n", bucket);
        if (words_match(word, dictionary_ll_node->word))
        {
            // printf("Words_match returned true. Match! Moving to next word.");
            return true;
        }
        // printf("Back in check(). Setting current node to next and checking again for a match.\n");
        dictionary_ll_node = dictionary_ll_node->next;
    }

    // we've traversed the entire linked list in that hashtable bucket and not found a match
    // printf("Linked-list traversed. No matching word found. \n");
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // for each bucket in the hashtable
    for (int i = 0; i < N; i++)
    {
        node *current_node = hashtable[i];
        // while there is a linked list node
        while (current_node != NULL)
        {
            node *temp_node = current_node;
            current_node = current_node->next;
            free(temp_node);
        }
        // if current_node started as NULL then there would be no ll nodes at that hashtable bucket location, so nothing to free
    }
    return true;
}

bool words_match(const char *word_1, const char *word_2)
{
    // printf("Word_Match func. Checking if '%s' matches '%s'. ", word_1, word_2);
    int word_len = strlen(word_1);
    // if they aren't the same length they can't be the same word
    if (word_len == strlen(word_2))
    {
        // compare the provided word against each word in that bucket
        // matching is case insensitive
        for (int i = 0; i < word_len; i++)
        {
            if (tolower(word_1[i]) != tolower(word_2[i]))
            {
                // printf("Text word and dictionary entry do not match %c != %c.\n", word_1[i], word_2[i]);
                return false;
            }
        } // all letters match, we found a match
        // printf("Match!\n");
        return true;
    }
    // word and dictionary entry are not of the same length so cannot be the same word
    // printf("Word lengths do not match!\n");
    return false;
}
