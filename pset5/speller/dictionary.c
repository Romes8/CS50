// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
int count_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = table[hash(word)];

    if (strcasecmp(cursor -> word, word) == 0)
    {
        return true;
    }

    while (cursor->next != NULL)
    {
        cursor = cursor -> next;

        if (strcasecmp(cursor -> word, word) == 0)
        {
            return true;
        }
    }
    printf("Words not in dictionary: %s\n", cursor->word);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int n = (int)tolower(word[0] - 97);
    return n;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    char *current_word = malloc(LENGTH);

    if (current_word == NULL)
    {
        return false;
    }

    while (fscanf(file, "%s", current_word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, current_word);
        count_words++;

        n->next = table[hash(current_word)];

        table[hash(current_word)] = n;
    }

    fclose(file);
    free(current_word);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int n = count_words;
    printf("Counted words: %i", n);
    return count_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *tmp;
    node *cursor;

    for (int i = 1; i < N; i++)
    {

        if (table[i] == NULL)
        {
            continue;
        }

        cursor = table[i];
        tmp = cursor;

        while (cursor->next != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        free(cursor);
    }
    return true;
}
