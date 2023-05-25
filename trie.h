#ifndef TRIE_H_
#define TRIE_H_

#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define ALPHABET_SIZE 26

// trie node definition
typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    char *value;
} TrieNode;

// function to create and initialize a new Trie node
TrieNode *createNode();

// function to insert a string into the Trie
void insert(TrieNode *root, char *key, char *value);

// function to search for a string in the Trie
char *search(TrieNode *root, char *key);

// function to free the memory allocated by the Trie
void freeTrie(TrieNode *root);

#endif