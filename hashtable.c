#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "utils.h"

#define TABLE_SIZE 100

unsigned int hash(char *key)
{
    unsigned int hash_value = 0;
    unsigned int i = 0;
    while (key[i] != '\0')
    {
        hash_value = (hash_value << 5) + key[i];
        i++;
    }
    return hash_value % TABLE_SIZE;
}

Entry *createEntry(char *key, int value)
{
    Entry *new_entry = (Entry *)malloc(sizeof(Entry));
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = NULL;
    return new_entry;
}

Hashtable *createHashtable()
{
    Hashtable *ht = (Hashtable *)malloc(sizeof(Hashtable));
    if (ht != NULL)
        for (int i = 0; i < TABLE_SIZE; i++)
            ht->table[i] = NULL;
    return ht;
}

void insertH(Hashtable *ht, char *key, int value)
{
    unsigned int index = hash(key);
    Entry *new_entry = createEntry(key, value);

    if (ht->table[index] == NULL)
        ht->table[index] = new_entry;
    else
    {
        Entry *current = ht->table[index];
        while (current->next != NULL)
            current = current->next;
        current->next = new_entry;
    }
}

int get(Hashtable *ht, char *key)
{
    unsigned int index = hash(key);
    Entry *current = ht->table[index];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    return 0;
}

void freeHashtable(Hashtable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Entry *current = ht->table[i];
        while (current != NULL)
        {
            Entry *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(ht);
}
