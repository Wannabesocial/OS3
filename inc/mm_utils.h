#ifndef MEMORY_MANAGER_UTILS_H
#define MEMORY_MANAGER_UTILS_H

#include "hash_table.h"
#include "config.h"

#include <sys/wait.h>

// Potition in stats table
#define READ  0
#define WRITE 1

typedef struct _stats{
    int operation[2];       // Read-Write
    int page_foult;         // Page Foults
    int traces_read;        // Entries examined from the trace files
    int allocated_frames;   // Max number of memory frames occupied.
    int flush;
}_stats;

/* -------------------------------------------------- */

/* Create exactly 2 CHILDRENS with properly COMMAND LINE ARGUMENTS */
void mmu_create_childrens(pid_t *child_pid, const int q_block_size, const int max);

/* Flush When Full Algorithm */
void mmu_FWF(_link_list *ht, const _trace *trace, const int size, const int k, int *cur_mem_space,
    const int mem_space, _stats *stats, int *max_frames_alocated);

/* Initilize the values from argument line and check if is correct */
void mmu_init_values(const int argc, char **argv, int *q_block_size, int *k, int *memory_space_per_process, int *max);

#endif