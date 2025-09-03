/* Implementation of the source code for the LINK LIST DATA STRUCTURE */

#include "link_list.h"

#include <stdio.h>
#include <stdlib.h>

void ll_init(_link_list *link_list){

    link_list->start = NULL;
    link_list->end = NULL;
}

void ll_print(const _link_list *link_list){

    // Traverse Throught the Link List
    for(_node *node = link_list->start; node != NULL; node = node->next){
        printf("%d,", node->page_number);
    }
}

bool ll_find(const _link_list *link_list, const _key key){

    for(_node *node = link_list->start; node != NULL; node = node->next){

        if(node->page_number == key){
            return true;
        }
    }
    return false;
}

bool ll_isEmpty(const _link_list *link_list){

    return (link_list->start == NULL || link_list->end == NULL)
        ? true
        : false;
}   

void ll_insert(_link_list *link_list, const int page_number){

    _node *new_node;

    if((new_node = (_node *) malloc(sizeof(_node))) == NULL){
        perror("Error in (ll_insert)");
        exit(EXIT_FAILURE);
    }

    // Init NODE data
    new_node->page_number = page_number;
    new_node->next = NULL;

    // Empty List = Insert first NODE. START and END must be the same
    if(ll_isEmpty(link_list)){
        link_list->start = new_node;
        link_list->end = new_node;
        return;
    }

    // Insert to end
    link_list->end->next = new_node;
    link_list->end = new_node;
}

void ll_remove(_link_list *link_list){

    _node *node = link_list->start; // Save first NODE

    link_list->start = link_list->start->next; // Second NODE become first

    // Remove last NODE = empty List. END and START must be the same
    if(ll_isEmpty(link_list)){
        link_list->end = link_list->start;
    }

    free(node);
}

void ll_destroy(_link_list *link_list){

    while(ll_isEmpty(link_list) == false){
        ll_remove(link_list);
    }
}
