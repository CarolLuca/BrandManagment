// Copyright <Carol-Luca Gasan, Teodora-Andreea Voicu>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "event.h"
#include "store.h"
#include "time.h"
#include "trie.h"
#include "utils.h"

#define MAX 30

int main()
{

    PriorityQueue *pq = createPriorityQueue();
    Hashtable *ht = createHashtable();
    TrieNode *trie = createNode();

    FILE *storeFile = fopen("in/stores.txt", "r");
    int numStores = 0;
    fscanf(storeFile, "%d\n", &numStores);
    Store *stores = (Store *)malloc(numStores * sizeof(Store));
    for (int i = 0; i < numStores; i++)
    {
        stores[i].name = (char *)malloc(100 * sizeof(char));
        stores[i].productCount = (int *)calloc(MAX, sizeof(int));
        fscanf(storeFile, "%s %d %d\n", stores[i].name, &stores[i].xCoordinate, &stores[i].yCoordinate);
        insertH(ht, stores[i].name, i);
    }
    fclose(storeFile);
    printf("There are %d stores!\n", numStores);

    while (1)
    {
        char eventTypeStr[MAX];
        fscanf(stdin, "%s", eventTypeStr);
        if (strcmp(eventTypeStr, "END") == 0)
            break;
        int type = 0;
        int hour = 0;
        int minute = 0;
        int second = 0;
        char *name = malloc(100 * sizeof(char));
        int *productCount = (int *)calloc(MAX, sizeof(int));
        if (strcmp(eventTypeStr, "Client") == 0)
        {
            type = 1;
            fscanf(stdin, "%d:%d:%d", &hour, &minute, &second);
            fscanf(stdin, "%s", name);
            int id = -1, buc = -1;
            while (fscanf(stdin, "%d %d", &id, &buc) == 2 && id != -1)
                productCount[id] += buc;
            int storeId = -1;
            char *Sname = malloc(100 * sizeof(char));
            fscanf(stdin, "%s", Sname);
            storeId = get(ht, Sname);
            enqueue(pq, createEvent(name, type, createTime(hour, minute, second), &(stores[storeId]), productCount));
            free(name);
            free(Sname);
            free(productCount);
            continue;
        }
        if (strcmp(eventTypeStr, "Manager") == 0)
        {
            type = 2;
            fscanf(stdin, "%d:%d:%d", &hour, &minute, &second);
            int storeId = -1;
            char *Sname = malloc(100 * sizeof(char));
            fscanf(stdin, "%s", Sname);
            storeId = get(ht, Sname);
            enqueue(pq, createEvent(name, type, createTime(hour, minute, second), &(stores[storeId]), productCount));
            free(name);
            free(Sname);
            free(productCount);
            continue;
        }
        if (strcmp(eventTypeStr, "StockUpdate") == 0)
        {
            type = 3;
            fscanf(stdin, "%d:%d:%d", &hour, &minute, &second);
            int id = -1, buc = -1;
            while (fscanf(stdin, "%d %d", &id, &buc) == 2 && id != -1)
                productCount[id] += buc;
            int storeId = -1;
            char *Sname = malloc(100 * sizeof(char));
            fscanf(stdin, "%s", Sname);
            storeId = get(ht, Sname);
            enqueue(pq, createEvent(name, type, createTime(hour, minute, second), &(stores[storeId]), productCount));
            free(name);
            free(Sname);
            free(productCount);
            continue;
        }
        type = 4;
        fscanf(stdin, "%d:%d:%d", &hour, &minute, &second);
        fscanf(stdin, "%s", name);
        enqueue(pq, createEvent(name, type, createTime(hour, minute, second), &(stores[0]), productCount));
        free(name);
        free(productCount);
    }

    printf("Ready to process events!\n\n");

    while (pq->size > 0)
    {
        Event *event = dequeue(pq);
        actEvent(&stores, numStores, pq, trie, event);
        freeEvent(event);
    }

    free(stores);
    freeHashtable(ht);
    freePriorityQueue(pq);
    freeTrie(trie);

    return 0;
}