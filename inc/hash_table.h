/* Here we have STRUCTS and FUNCTIONS related to a HASH TABLE implementation.
A HASH TABLE where every entry is a LINK LIST */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "link_list.h"

#define HASH_TABLE_SIZE 16
#define hash_function(page_number) (page_number % HASH_TABLE_SIZE) // [0, HASH_TABLE_SIZE)

/* ---------------------------------------------- */

/* Initialize */
void ht_init(_link_list *hash_table);

/* Print contents ,usefull to ensure all works well */
void ht_print(const _link_list *hash_table);

/* Find if node with key exist */
bool ht_find(const _link_list *hash_table, const int entry, const _key key);

/* Insert */
void ht_insert(_link_list *hash_table, const int entry, const int page_number);

/* Destroy all the data */
void ht_destroy(_link_list *hash_table);

#endif