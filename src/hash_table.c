#include "hash_table.h"

#include <stdio.h>

void ht_init(_link_list *hash_table){

    // Initialize every entry
    for(int i = 0; i < HASH_TABLE_SIZE; i++){
        ll_init(&hash_table[i]);
    }
}

void ht_print(const _link_list *hash_table){

    printf("Hash table DATA\n");

    // Traverse throught every entry
    for(int i = 0; i < HASH_TABLE_SIZE; i++){
        printf("Entry %d: ", i);
        ll_print(&hash_table[i]);
        printf("\n");
    }
}

bool ht_find(const _link_list *hash_table, const int entry, const _key key){
    return ll_find(&hash_table[entry], key);
} 

void ht_insert(_link_list *hash_table, const int entry, const int page_number){
    ll_insert(&hash_table[entry], page_number);
}

void ht_destroy(_link_list *hash_table){

    // Destroy every entry
    for(int i = 0; i < HASH_TABLE_SIZE; i++){
        ll_destroy(&hash_table[i]);
    }
}
