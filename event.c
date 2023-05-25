#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"
#include "store.h"
#include "utils.h"
#include "event.h"
#include "time.h"
#include "trie.h"

#define MAX 30

Event *createEvent(char *name, int type, Time *time, Store *store, int *productCount)
{
    Event *event = malloc(sizeof(Event));
    event->name = strdup(name);
    event->type = type;
    event->time = time;
    event->store = store;
    event->productCount = (int *)calloc(MAX, sizeof(int));
    event->productExistence = 0;
    for (int i = 0; i < MAX; ++i)
    {
        if (productCount[i])
            event->productExistence |= (1 << i);
        event->productCount[i] = productCount[i];
    }
    return event;
}

void freeEvent(Event *event)
{
    if (event == NULL)
        return;
    free(event->name);
    free(event->time);
    free(event->productCount);
    free(event);
}

PriorityQueue *createPriorityQueue()
{
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    queue->events = NULL;
    queue->size = 0;
    return queue;
}

void enqueue(PriorityQueue *queue, Event *event)
{
    queue->size++;
    queue->events = (Event **)realloc(queue->events, sizeof(Event *) * queue->size);
    queue->events[queue->size - 1] = event;

    int currentIndex = queue->size - 1;
    int parentIndex = (currentIndex - 1) / 2;

    while (currentIndex > 0 && compareTimes(queue->events[currentIndex]->time, queue->events[parentIndex]->time) < 0)
    {
        Event *temp = queue->events[currentIndex];
        queue->events[currentIndex] = queue->events[parentIndex];
        queue->events[parentIndex] = temp;

        currentIndex = parentIndex;
        parentIndex = (currentIndex - 1) / 2;
    }
}

Event *dequeue(PriorityQueue *queue)
{
    if (queue->size == 0)
        return NULL;

    Event *minEvent = queue->events[0];
    queue->events[0] = queue->events[queue->size - 1];
    queue->size--;

    queue->events = (Event **)realloc(queue->events, sizeof(Event *) * queue->size);

    int currentIndex = 0;
    int leftChildIndex = 2 * currentIndex + 1;
    int rightChildIndex = 2 * currentIndex + 2;
    int smallestIndex;

    while (1)
    {
        if (leftChildIndex < queue->size && compareTimes(queue->events[leftChildIndex]->time, queue->events[currentIndex]->time) < 0)
            smallestIndex = leftChildIndex;
        else
            smallestIndex = currentIndex;

        if (rightChildIndex < queue->size && compareTimes(queue->events[rightChildIndex]->time, queue->events[smallestIndex]->time) < 0)
            smallestIndex = rightChildIndex;

        if (smallestIndex == currentIndex)
            break;

        Event *temp = queue->events[currentIndex];
        queue->events[currentIndex] = queue->events[smallestIndex];
        queue->events[smallestIndex] = temp;

        currentIndex = smallestIndex;
        leftChildIndex = 2 * currentIndex + 1;
        rightChildIndex = 2 * currentIndex + 2;
    }

    return minEvent;
}

void freePriorityQueue(PriorityQueue *queue)
{
    if (queue == NULL)
        return;

    for (int i = 0; i < queue->size; i++)
        freeEvent(queue->events[i]);

    free(queue->events);
    free(queue);
}

void actEvent(Store **storeArray, int storeCount, PriorityQueue *pq, TrieNode *root, Event *event)
{
    printf("Time: %02d-%02d-%02d\n", event->time->hour, event->time->minute, event->time->second);
    if (event->type == Client)
    {
        printf("Client: %s\n", event->name);
        if ((event->productExistence & event->store->productExistence) != 0)
            insert(root, event->name, event->store->name);
        int *remainCount = (int *)calloc(MAX, sizeof(int));
        int remainExistance = 0;
        for (int i = 0; i < MAX; ++i)
            if (event->productCount[i] > 0)
            {
                if (event->store->productCount[i] == 0)
                {
                    remainExistance |= (1 << i);
                    remainCount[i] = event->productCount[i];
                }
                else
                {
                    event->productCount[i] = min(event->productCount[i], event->store->productCount[i]);
                    updateProduct(event->store, i, -event->productCount[i]);
                }
            }
        if (remainExistance == 0)
        {
            printf("He bought all his desired products from %s\n\n", event->store->name);
            return;
        }
        Store *newStore = malloc(sizeof(Store));
        newStore = closestStore(storeArray, storeCount, event->store, remainExistance);
        if (newStore == NULL)
        {
            printf("He cannot buy all of his desired products at all\n\n");
            return;
        }
        printf("Redirected for the rest of his products to %s\n\n", newStore->name);
        Event *newEvent = createEvent(event->name, Client,
                                      addTime(event->time, (int)distanceStores(event->store, newStore)),
                                      newStore, remainCount);
        enqueue(pq, newEvent);
        return;
    }

    if (event->type == Manager)
    {
        char fileName[100];
        snprintf(fileName, sizeof(fileName), "out/%s_%02d-%02d-%02d.txt", event->store->name, event->time->hour, event->time->minute, event->time->second);

        FILE *file = fopen(fileName, "w");

        if (file == NULL)
        {
            printf("Error opening file.\n");
            return;
        }

        fprintf(file, "Store: %s\n", event->store->name);
        fprintf(file, "Time: %02d:%02d:%02d\n", event->time->hour, event->time->minute, event->time->second);

        fprintf(file, "Product Database:\n");
        for (int i = 0; i < MAX; i++)
            fprintf(file, "Product %d: %d\n", i, event->store->productCount[i]);

        fclose(file);
        printf("Manager obtained his list\n\n");
        return;
    }

    if (event->type == StockUpdate)
    {
        printf("Store: %s\n", event->store->name);
        printf("The stock update was successful\n\n");
        for (int i = 0; i < MAX; ++i)
            updateProduct(event->store, i, event->productCount[i]);
        return;
    }

    char *answer = search(root, event->name);
    if (answer)
        printf("Valid feedback!\nLast shopping experience of %s is at %s\n\n", event->name, answer);
    else
        printf("Invalid feedback!\n%s did not shop lately\n\n", event->name);
}
