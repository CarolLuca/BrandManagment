#ifndef STORE_H_
#define STORE_H_

#include <stdlib.h>
#include "utils.h"
#define MAX 30

// struct to store a Store's details
struct store
{
    char *name;
    int productExistence;
    int *productCount;
    int xCoordinate;
    int yCoordinate;
};
typedef struct store Store;

// creates a Store instance
Store *createStore(char *name, int *productCount, int xCoordinate, int yCoordinate);

// calculates the distance between two stores
double distanceStores(Store *store1, Store *store2);

// finds the closest store to a given one that has a range of products in stock
Store *closestStore(Store **storeArray, int storeCount, Store *currStore, int reqProducts);

// adds to a given store a count of items of a certain product
void updateProduct(Store *store, int product, int count);

// function to clear store instance
void freeStore(Store *store);

#endif