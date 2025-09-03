/* Here we have STRUCTS and FUNCTIONS related to a LINK LIST implementation */

#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <stdbool.h>

typedef int _key;

/* Node of Link List. No need to store Frame Number couse project
does not require to use it somewere */
typedef struct _node{
    int page_number;    // The page that corresponds to the logical address (most left 20-bit)
    struct _node *next;
}_node;

/* Link List, O(1) insert and remove, with 2 pointers */
typedef struct _link_list{
    _node *start;   // Insert only in the end
    _node *end;     // Remove only from the start
}_link_list;

/* ---------------------------------------------- */

/* Initialize */
void ll_init(_link_list *link_list);

/* Print contents ,usefull to ensure all works well */
void ll_print(const _link_list *link_list);

/* Check if is EMPTY */
bool ll_isEmpty(const _link_list *link_list);

/* Find if a node with a specific key exist */
bool ll_find(const _link_list *link_list, const _key key);

/* Insert data */
void ll_insert(_link_list *link_list, const int page_number);

/* Remove data. We do not take back the NODE data */
void ll_remove(_link_list *link_list);

/* Destroy everything */
void ll_destroy(_link_list *link_list);

#endif