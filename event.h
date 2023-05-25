#ifndef EVENT_H_
#define EVENT_H_

#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"
#include "store.h"
#include "utils.h"
#include "time.h"
#include "trie.h"

#define MAX 30

// defining event types
enum eventTypes
{
    Client = 1,
    Manager = 2,
    StockUpdate = 3,
    Feedback = 4
};

// event definition
struct event
{
    char *name;
    Time *time;
    Store *store;
    enum eventTypes type;
    int productExistence;
    int *productCount;
};
typedef struct event Event;

// function to create event instance
Event *createEvent(char *name, int type, Time *time, Store *store, int *productCount);

// function to free event instance
void freeEvent(Event *event);

// pq definition
struct priorityQueue
{
    Event **events;
    int size;
};
typedef struct priorityQueue PriorityQueue;

// function to create pq instance
PriorityQueue *createPriorityQueue();

// function to enqueue
void enqueue(PriorityQueue *queue, Event *event);

// function to get the top of a pq
Event *dequeue(PriorityQueue *queue);

// function to free pq
void freePriorityQueue(PriorityQueue *queue);

// function to proceed with a certain event
void actEvent(Store **storeArray, int storeCount, PriorityQueue *pq, TrieNode *root, Event *event);

#endif