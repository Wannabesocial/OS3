#include "mm_utils.h"
#include "ipc.h"

#include <stdio.h>
#include <unistd.h>

void mmu_create_childrens(pid_t *child_pid, const int q_block_size, const int max){

    int pid;

    // Argument Line commands for CHILDRENS
    char arr[3][10];
    sprintf(arr[P_BLOCK_SIZE], "%d", q_block_size);
    sprintf(arr[P_MAX_ROWS], "%d", max);

    for(int i = 0; i < 2; i++){

        sprintf(arr[P_POTITION], "%d", i);

        pid = fork();
        switch(pid){

            case -1:
                handle_error("Error in (memory_manager.c), fork()");

            case 0:
                execlp("./page_manager", arr[P_BLOCK_SIZE], arr[P_MAX_ROWS], arr[P_POTITION], NULL);
            
            default:
                child_pid[i] = pid;
                break;
        }
    }
}

void mmu_FWF(_link_list *ht, const _trace *trace, const int size, const int k, int *cur_mem_space,
    const int mem_space, _stats *stats, int *max_frames_alocated){

    int entry, cur_k = 0;

    for(int i = 0; i < size; i++){

        if(trace[i].logical_address == NO_DATA){
            break;
        }

        // We have a trace
        stats->traces_read++;
        entry = hash_function(trace[i].logical_address);

        // Already in memory
        if(ht_find(ht, entry, trace[i].logical_address) == true){
            continue;
        }

        // We just got Page Fault
        stats->page_foult++;
        cur_k++;

        // We must Flush the HASHED PAGE TABLE, and do RESETS
        if(cur_k == k+1){
            ht_destroy(ht);
            stats->flush++;
            cur_k = 0;
            *cur_mem_space = 0;
            *max_frames_alocated -= mem_space; 
        }

        // No memory in "RAM"
        if(*cur_mem_space+1 > mem_space){
            continue;
        }

        // We can finaly insert in HASHED PAGE TABLE
        (*cur_mem_space)++;
        (*max_frames_alocated)++;
        if(stats->allocated_frames < *max_frames_alocated){
            stats->allocated_frames = *max_frames_alocated;
        }

        (trace[i].operation == 'R') ? stats->operation[READ]++ : stats->operation[WRITE]++;
        ht_insert(ht, entry, trace[i].logical_address);        
    }
}

void mmu_init_values(const int argc, char **argv, int *q_block_size, int *k, int *memory_space_per_process, int *max){

    // We take lees tha the minimum or more than the maximun arguments.
    if(argc < 4 || argc > 5){
        handle_error("Not right number of arguments");
    }

    *q_block_size = atoi(argv[1]);
    *k = atoi(argv[2]);
    *memory_space_per_process = atoi(argv[3]) / 2;
    *max = (argc == 5) ? atoi(argv[4]) : NO_CAP;    // 5 means MAX was given
}
