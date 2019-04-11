#include "map.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/** TODO */
typedef struct node_t {
    void *key;
    void *data;
    struct node_t *next;
} *Node;

/** TODO */
struct Map_t {
    Node *base;
    Node node_iterator;
    MapKeyElement *iterator;
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
    if ((!copyDataElement) || (!copyKeyElement) || (!freeDataElement) || (!compareKeyElements)) {
        return NULL;
    }
    Map map = malloc(sizeof(*map));
    if (map == NULL) {
        return NULL;
    }
    map->base = NULL;
    map->node_iterator = malloc(sizeof(*map->node_iterator));
    if(!map->node_iterator) {
        return NULL;
    }
    map->iterator = malloc(sizeof(*map->iterator));
    if(!map->iterator) {
        return NULL;
    }
    map->copyData = copyDataElement;
    map->copyKey = copyKeyElement;
    map->freeData = freeDataElement;
    map->freeKey = freeKeyElement;
    map->compareKey = compareKeyElements;
}

MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement){
    Node new = malloc(sizeof(*new));
    if(!new) {
        return MAP_OUT_OF_MEMORY;
    }
    new->key = map->copyKey(keyElement);
    new->data = map->copyData(dataElement);
    new->next = NULL;
    if (!map->base) {
        map->base = &new;
    }
    else {
        MAP_FOREACH(MapKeyElement, iterator, map){
            break;
        /* TODO: not completed yet */
        }
    }
    return MAP_SUCCESS;
}

MapKeyElement mapGetFirst(Map map){
    map->node_iterator = *(map->base);
    map->iterator = (map->node_iterator)->key;
    return map->iterator;
}

MapKeyElement mapGetNext(Map map){
    map->node_iterator = map->node_iterator->next;
    map->iterator = (map->node_iterator)->key;
    return map->iterator;
}
