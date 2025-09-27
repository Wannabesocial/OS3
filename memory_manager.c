/* The main proccess MM that will track STATISTICKS and manage the HASHED PAGE TABLE */

#include "link_list.h"
#include "hash_table.h"
#include "config.h"
#include "ipc.h"
#include "mm_utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/mman.h>

int main(int argc, char **argv){

    // Data from User, usefull for Page Manager
    int q_block_size = 0, max = 0, k = 0, memory_space_per_process = 0;

    mmu_init_values(argc, argv, &q_block_size, &k, &memory_space_per_process, &max);

    // Delete existed IPCS
    shm_unlink(SHARED_MEM_NAME);
    sem_unlink(SEM_NAME[0]); sem_unlink(SEM_NAME[1]); sem_unlink(SEM_NAME[2]);

    _link_list hash_table[2][HASH_TABLE_SIZE];
    ht_init(hash_table[0]); ht_init(hash_table[1]);

    pid_t children[2], pid;

    // Statistics
    _stats stats;
    memset(&stats, 0, sizeof(stats)); 

    int cur_mem_space[2] = {0, 0}, max_frames_alocated = 0;

    // Make POSIX SEMAPHORES
    sem_t *semaphore[3];
    for(int i = 0; i < 3; i++){
        semaphore[i] = sem_open(SEM_NAME[i], O_CREAT | O_EXCL, 0700, 0);
    }

    // Make POSIX SHARED MEMMORY
    int fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_EXCL | O_RDWR, 0700);
    ftruncate(fd, sizeof(_shared_memory));
    _shared_memory *shared_mem = mmap(NULL, sizeof(_shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Time to make some CHILDRENS aka Page Managers
    mmu_create_childrens(children, q_block_size, max);

    // Simulation
    bool end = false, last_chunk;
    _trace *trace;
    int trace_read, j ;

    if((trace = (_trace *) malloc(sizeof(_trace) * q_block_size)) == NULL){
        handle_error("Error in (malloc), memory_manager.c");
    }

    while(end == false){

        // For both child processes
        for(int i = 0; i < 2; i++){

            trace_read = 0;
            last_chunk = false;

            memset(trace, NO_DATA, sizeof(_trace) * q_block_size);

            // Until we read all the q_block_Size
            while(last_chunk == false){

                sem_post(semaphore[i]);
                sem_wait(semaphore[MM_SEMAPHORE]);

                end = shared_mem->terminate;
                if(end == true)
                    break;

                last_chunk = shared_mem->last_chunk;

                // Temporary save all the q_block_Size. We do this couse shared memory may be less than q_block_Size
                for(j = 0; j < SHARED_BUFF_SIZE; j++){

                    if(shared_mem->buffer[j].logical_address == NO_DATA){
                        break;
                    }

                    trace[j+trace_read].logical_address = shared_mem->buffer[j].logical_address;
                    trace[j+trace_read].operation = shared_mem->buffer[j].operation;
                }   

                trace_read += j;
            }

            // HASH PAGE TABLE
            if(end != true)
                mmu_FWF(hash_table[i], trace, q_block_size, k, &cur_mem_space[i], memory_space_per_process, &stats, &max_frames_alocated);
        }
    }

    // Collect zombie processes. They have terminated properly
    for(int i = 0; i < 2; i++){
        wait(NULL);
    }

    // Delete Shared Memory
    munmap(shared_mem, sizeof(_shared_memory));
    close(fd);
    shm_unlink(SHARED_MEM_NAME);

    // Delete Semaphores
    for(int i = 0; i < 3; i++){
        sem_close(semaphore[i]);
        sem_unlink(SEM_NAME[i]);
    }

    ht_destroy(hash_table[0]); ht_destroy(hash_table[1]);

    printf("STATS\n");
    printf("R:%d, W:%d, PF:%d, TRACE:%d FLUSH:%d MAX FRAMES:%d\n", stats.operation[READ], stats.operation[WRITE],
        stats.page_foult, stats.traces_read, stats.flush, stats.allocated_frames);

    free(trace);

    return 0;
}