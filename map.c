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

int mapGetSize(Map map){
    if (map==NULL){
        return ERROR;
    }
    int counter=1;
    Node next_ptr=(*(map->base))->next;
    while(next_ptr!=NULL){
        counter+=1;
        next_ptr=next_ptr->next;
    }
    return counter;

}

bool mapContains(Map map, MapKeyElement element){
    if(map==NULL || element==NULL){
        return false;
    }
    Node first_node=(*(map->base));
    MapKeyElement current_key=first_node->key;
    Node next_node=first_node->next;
    while(next_node!=NULL){
        if((map->compareKey(current_key,element))==0){
            return true;
        }
        next_node=next_node->next;
    }
    return false;
}

MapResult mapClear(Map map){
    if(map==NULL){
        return MAP_NULL_ARGUMENT;
    }
    Node node=(*map->base);
    while(node!=NULL){
        MapDataElement node_data=node->data;
        MapKeyElement  node_key=node->key;
        Node next_node=node->next;
        map->freeData(node_data);
        map->freeKey(node_key);
        free(node);
        node=next_node;

    }
    *map->base=NULL;
    return MAP_SUCCESS;

}

void mapDestroy(Map map){
    if(map==NULL){
        return;
    }
    mapClear(map);
    free(map);
    return;
}

Map mapCopy(Map map){

}