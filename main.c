#include <stdio.h>
#include <stdlib.h>
#include "map.h"


/** Function to be used for copying an int as a key to the map */
static MapKeyElement copyKeyInt(MapKeyElement n) {
    if (!n) {
        return NULL;
    }
    int *copy = malloc(sizeof(*copy));
    if (!copy) {
        return NULL;
    }
    *copy = *(int *) n;
    return copy;
}

/** Function to be used for copying a char as a data to the map */
static MapDataElement copyDataChar(MapDataElement n) {
    if (!n) {
        return NULL;
    }
    char *copy = malloc(sizeof(*copy));
    if (!copy) {
        return NULL;
    }
    *copy = *(char *) n;
    return (MapDataElement) copy;
}

/** Function to be used by the map for freeing elements */
static void freeInt(MapKeyElement n) {
    free(n);
}

/** Function to be used by the map for freeing elements */
static void freeChar(MapDataElement n) {
    free(n);
}

/** Function to be used by the map for comparing elements */
static int compareInts(MapKeyElement n1, MapKeyElement n2) {
    return (*(int *) n1 - *(int *) n2);
}

bool testMapCreateDestroy() {
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    return true;
}

bool testIterator() {
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);

    for (int i = 1; i < 400; ++i) {
        char j = (char) i;
        ++j;
        mapPut(map, &i, &j);
    }

    for (int i = 800; i >= 400; --i) {
        char j = (char) i;
        ++j;
        if (mapPut(map, &i, &j) != MAP_SUCCESS){
            return false;
        }
    }

    for (int i = 801; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        if (mapPut(map, &i, &j) != MAP_SUCCESS){
            return false;
        }
    }

    int i = 1;
    MAP_FOREACH(int *, iter, map) {
        if (*iter != i) {
            printf("%d key: %d\n", i, *iter);
        }
        i++;
    }

    return true;
}

int main(){
    bool check;
    check = testIterator();
    printf("%d", check);
    return 0;
}