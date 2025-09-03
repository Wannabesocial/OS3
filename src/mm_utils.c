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
