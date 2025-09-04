/* Code for the PM. This will be forked so we will have 2 PM processes */

#include "ipc.h"
#include "config.h"

#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char **argv){

    int p = atoi(argv[P_POTITION]);

    printf("SEM:%s FILE:%s\n", SEM_NAME[p], TRACE_FILE[p]);
    

    /* Data from ARGUMENT LINE */
    int q_block_size = atoi(argv[P_BLOCK_SIZE]), max_rows = atoi(argv[P_MAX_ROWS]); // From user q, k, max, respectfully


    
    const char *file_name = TRACE_FILE[0];

    FILE *trace_file;
    int remaining_rows;

    /* base on ROWS and BLOCK size from user, on BLOCK from user and SHARED MEMMORY limitations */
    int total_reads1, total_reads2;

    /* base on remaining from total_reads1, on total_reads2 */
    int block_size1, block_size2;

    // Semaphore shits
    sem_t *PM_semaphore, *MM_semaphore;
    PM_semaphore = sem_open(SEM_NAME[p], O_CREAT);
    MM_semaphore = sem_open(SEM_NAME[MM_SEMAPHORE], O_CREAT);

    // Shared Memory shits
    int fd = shm_open(SHARED_MEM_NAME, O_RDWR, 0);
    _shared_memory *shared_memory = mmap(NULL, sizeof(_shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);



    if((trace_file = fopen(file_name, "r")) == NULL){
        handle_error("Error in (page_manager.c), fopen()"); 
    }

#if 1 == 1
    max_rows = (max_rows == NO_CAP) ? cf_rows(trace_file) : max_rows; // Specify MAX rows

    total_reads1 = ceil((double) max_rows / q_block_size);
    for(int i = 0; i < total_reads1; i++){

        remaining_rows = max_rows - i * q_block_size;
        block_size1 = (remaining_rows > q_block_size) ? q_block_size : remaining_rows;

        total_reads2 = ceil((double) block_size1 / SHARED_BUFF_SIZE);
        for(int i = 0; i < total_reads2; i++){

            remaining_rows = block_size1 - i * SHARED_BUFF_SIZE;
            block_size2 = (remaining_rows > SHARED_BUFF_SIZE) ? SHARED_BUFF_SIZE : remaining_rows;
            

            // Enter CS
            sem_wait(PM_semaphore);

            // Just Call Read function with BLOCK_SIZE2 XD!
            cf_read(shared_memory->buffer, block_size2, trace_file);

            sem_post(MM_semaphore);
            // Exit CS
        }
    }


    // Now MM can terminate
    sem_wait(PM_semaphore);
    shared_memory->terminate = true;
    sem_post(MM_semaphore);

#endif
    fclose(trace_file);

    // Close Semaphores
    sem_close(PM_semaphore);
    sem_close(MM_semaphore);
    
    // Close Share Memory
    munmap(shared_memory, sizeof(_shared_memory));
    close(fd);

    return 0;
}
