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


void wtf(_trace *buff){

    for(int i = 0; i < SHARED_BUFF_SIZE; i++){

        if(buff[i].logical_address == NO_DATA){
            return;
        }

        printf("Address:%x\t Operation:%c\n", buff[i].logical_address, buff[i].operation);
    }
}


int main(int argc, char **argv){

    // Delete existed IPCS
    shm_unlink(SHARED_MEM_NAME);
    sem_unlink(SEM_NAME[0]); sem_unlink(SEM_NAME[1]); sem_unlink(SEM_NAME[2]);

    //_link_list hash_table[HASH_TABLE_SIZE];
    pid_t children[2], pid;
    int status;

    // Data from User, usefull for Page Manager
    int q_block_size = 2, max = 2;

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
    _shared_memory mem_instance = {.terminate = false}; // Temporary save of SHARED MEMORY instans
    while(mem_instance.terminate == false){

        sem_post(semaphore[PM1_SEMAPHORE]);
        sem_wait(semaphore[MM_SEMAPHORE]);
        // CS1 for PM1

        memcpy(&mem_instance, shared_mem, sizeof(_shared_memory));
        printf("CS1\n");
        wtf(mem_instance.buffer);


        sem_post(semaphore[PM2_SEMAPHORE]);
        sem_wait(semaphore[MM_SEMAPHORE]);
        // CS2 for PM2

        memcpy(&mem_instance, shared_mem, sizeof(_shared_memory));
        printf("CS2\n");
        //wtf(mem_instance.buffer);
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

    return 0;
}