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
    Node base;
    Node node_iterator;
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
        free(map);
        return NULL;
    }
    map->base = NULL;
    map->node_iterator = malloc(sizeof(*map->node_iterator));
    if(!map->node_iterator) {
        free(map->node_iterator);
        free(map);
        return NULL;
    }
    map->node_iterator=NULL;

    map->copyData = copyDataElement;
    map->copyKey = copyKeyElement;
    map->freeData = freeDataElement;
    map->freeKey = freeKeyElement;
    map->compareKey = compareKeyElements;
    return map;
}

MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement){
    if((!keyElement) || (!dataElement)|| (!map)){
        return MAP_NULL_ARGUMENT;
    }
    Node new = malloc(sizeof(*new));
    if(!new) {
        free(new);
        return MAP_OUT_OF_MEMORY;
    }
    new->key = map->copyKey(keyElement);
    new->data = map->copyData(dataElement);
    new->next = NULL;
    if (!map->base){
        map->base = new;
        return MAP_SUCCESS;
    }
    else {
        MAP_FOREACH(MapKeyElement, iterator, map) {
            if (!map->node_iterator->next) {
                map->node_iterator->next = new;
                return MAP_SUCCESS;
            }
            else if (map->compareKey(map->node_iterator->next->key, keyElement)==0){
                map->node_iterator->next->data = map->copyData(dataElement);
                free(new);
                return MAP_SUCCESS;
            }
            else if (map->compareKey(map->node_iterator->next->key, keyElement)>0){
                new->next = map->node_iterator->next;
                map->node_iterator->next = new;
                return MAP_SUCCESS;
            }
        }
    }
    return MAP_SUCCESS;
}

MapDataElement mapGet(Map map, MapKeyElement keyElement){
    if((!keyElement) || (!map)){
        return NULL;
    }
    Node iter = malloc(sizeof(*iter));
    if(!iter) {
        free(iter);
        return NULL;
    }
    iter = map->base;
    while(iter->next){
        if (map->compareKey(iter->key,keyElement) == 0) {
            free(iter);
            return iter->data;
        }
        iter = iter->next;
    }
    free(iter);
    return NULL;
}

MapResult mapRemove(Map map, MapKeyElement keyElement){
    if((!keyElement) || (!map)){
        return MAP_NULL_ARGUMENT;
    }
    MAP_FOREACH(MapKeyElement, iterator, map){
        if (map->compareKey(map->node_iterator->next->key, keyElement)==0){
            map->freeKey(map->node_iterator->next->key);
            map->freeData(map->node_iterator->next->data);
            free(map->node_iterator->next);
            map->node_iterator->next = map->node_iterator->next->next;
        }
    }
    return MAP_ITEM_DOES_NOT_EXIST;
}

MapKeyElement mapGetFirst(Map map){
    if (!map) {
        return NULL;
    }
    if (!map->base){
        return NULL;
    }
    map->node_iterator = map->base;
    return map->node_iterator->key;
}

MapKeyElement mapGetNext(Map map){
    if (!map) {
        return NULL;
    }
    if(!map->node_iterator->next) {
        return NULL;
    }
    map->node_iterator = map->node_iterator->next;
    return map->node_iterator->key;
}