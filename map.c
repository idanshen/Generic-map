#include "map.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define ERROR -1

/** TODO */
typedef struct node_t {
    void *key;
    void *data;
    struct node_t *next;
} *Node;

/** TODO */
struct Map_t {
    Node *base;
    copyMapDataElements copyData;
    copyMapKeyElements copyKey;
    freeMapDataElements freeData;
    freeMapKeyElements freeKey;
    compareMapKeyElements compareKey;
};

Map mapCreate(copyMapDataElements copyDataElement,
              copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement,
              freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements) {
    Map map = malloc(sizeof(*map));
    if (map == NULL) {
        return NULL;
    }
    map->base = NULL;
    map->copyData = copyDataElement;
    map->copyKey = copyKeyElement;
    map->freeData = freeDataElement;
    map->freeKey = freeKeyElement;
    map->compareKey = compareKeyElements;
}