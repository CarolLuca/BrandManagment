#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Define the structure for hashtable entry
typedef struct Entry
{
    char *key;
    int value;
    struct Entry *next;
} Entry;

// Define the structure for hashtable
typedef struct Hashtable
{
    Entry *table[TABLE_SIZE];
} Hashtable;

// Hash function
unsigned int hash(char *key);

// Create a new hashtable entry
Entry *createEntry(char *key, int value);

// Create a new hashtable instance
Hashtable *createHashtable();

// Insert an entry into the hashtable
void insertH(Hashtable *ht, char *key, int value);

// Retrieve a value from the hashtable based on the key
int get(Hashtable *ht, char *key);

// Free the memory used by the hashtable
void freeHashtable(Hashtable *ht);

#endif