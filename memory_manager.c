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
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/mman.h>

int main(int argc, char **argv){

    // DO a clean-up SEMAHPORES and SHARED MEMORY for safty

#if 1 == 0
    //_link_list hash_table[HASH_TABLE_SIZE];
    pid_t children[2], pid;
    int status;

    // Data from User, usefull for Page Manager
    int q_block_size = 10, max = 100;

    // Make POSIX SEMAPHORES
    sem_t *sem_set_up[2];
    sem_set_up[0] = sem_open(SEM_NAME_SETUP[0], O_CREAT | O_EXCL, 0600, 0);
    sem_set_up[1] = sem_open(SEM_NAME_SETUP[1], O_CREAT | O_EXCL, 0600, 0);

    // Make POSIX SHARED MEMMORY
    int shared_mem_id[2];
    shared_mem_id[0] = shm_open(SHARED_MEM_NAME[0], O_CREAT | O_EXCL, 0600);
    shared_mem_id[1] = shm_open(SHARED_MEM_NAME[1], O_CREAT | O_EXCL, 0600);

    ftruncate(shared_mem_id[0], sizeof(_shared_memory));
    ftruncate(shared_mem_id[1], sizeof(_shared_memory));

    _shared_memory *shared_mem[2];
    shared_mem[0] = mmap(NULL, sizeof(_shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED, shared_mem_id[0], 0);
    shared_mem[1] = mmap(NULL, sizeof(_shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED, shared_mem_id[1], 0);

    // Time to make some CHILDRENS aka Page Managers
    mmu_create_childrens(children, q_block_size, max);

    // Ensure both Childs Execute Right. If something goes wrong terminate both processes

    // PM1 ready sem
    // PM2 ready sem

    // go shared memmory and see. If BOTH flags != terminated all good

    // Collect zombie processes. They have terminated properly
    for(int i = 0; i < 2; i++){
        wait(NULL);
    }

    printf("Childrens ID:%d, %d\n", children[0], children[1]);

    // Delete Semaphores SET-UP
    sem_unlink(SEM_NAME_SETUP[0]);
    sem_unlink(SEM_NAME_SETUP[1]);

    // Delete Shared Memory
    shm_unlink(SHARED_MEM_NAME[0]);
    shm_unlink(SHARED_MEM_NAME[1]);
#endif
    return 0;
}