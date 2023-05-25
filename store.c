#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "store.h"
#include "utils.h"

#define MAX 30

Store *createStore(char *name, int *productCount, int xCoordinate, int yCoordinate)
{
    Store *storeInst = malloc(sizeof(Store));
    storeInst->name = strdup(name);
    storeInst->xCoordinate = xCoordinate;
    storeInst->yCoordinate = yCoordinate;
    storeInst->productCount = (int *)calloc(MAX, sizeof(int));
    storeInst->productExistence = 0;
    for (int i = 0; i < MAX; ++i)
    {
        if (productCount[i] > 0)
            storeInst->productExistence |= (1 << i);
        storeInst->productCount[i] = productCount[i];
    }
    return storeInst;
}

double distanceStores(Store *store1, Store *store2)
{
    int dx = store1->xCoordinate - store2->xCoordinate;
    int dy = store1->yCoordinate - store2->yCoordinate;
    return (double)sqrt(1. * dx * dx + 1. * dy * dy);
}

Store *closestStore(Store **storeArray, int storeCount, Store *currStore, int reqProducts)
{
    int index = -1;
    double minDistance = 10000.;
    for (int i = 0; i < storeCount; ++i)
        if ((storeArray[i]->xCoordinate != currStore->xCoordinate ||
             storeArray[i]->xCoordinate != currStore->xCoordinate) &&
            ((storeArray[i]->productExistence & reqProducts) == reqProducts) &&
            distanceStores(storeArray[i], currStore) < minDistance)
        {
            minDistance = distanceStores(storeArray[i], currStore);
            index = i;
        }
    if (index == -1)
        return NULL;
    return storeArray[index];
}

void updateProduct(Store *store, int product, int count)
{
    if (count == 0)
        return;
    store->productCount[product] += count;
    if (store->productCount == 0)
        store->productExistence &= ~(1 << product);
    else
        store->productExistence |= (1 << product);
}

void freeStore(Store *store)
{
    free(store->name);
    free(store->productCount);
    free(store);
}