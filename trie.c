#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "utils.h"

#define ALPHABET_SIZE 26

TrieNode *createNode()
{
    TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));
    newNode->value = NULL;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        newNode->children[i] = NULL;

    return newNode;
}

void insert(TrieNode *root, char *key, char *value)
{
    int length = strlen(key);
    TrieNode *current = root;

    for (int level = 0; level < length; level++)
    {
        int index = key[level] - 'a';

        if (current->children[index] == NULL)
            current->children[index] = createNode();

        current = current->children[index];
    }

    if (current->value != NULL)
        free(current->value);
    current->value = strdup(value);
}

char *search(TrieNode *root, char *key)
{
    int length = strlen(key);
    TrieNode *current = root;

    for (int level = 0; level < length; level++)
    {
        int index = key[level] - 'a';

        if (current->children[index] == NULL)
            return NULL;

        current = current->children[index];
    }

    if (current != NULL && current->value != NULL)
        return current->value;

    return NULL;
}

void freeTrie(TrieNode *root)
{
    if (root == NULL)
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        freeTrie(root->children[i]);

    free(root->value);
    free(root);
}
