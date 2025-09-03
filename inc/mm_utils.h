#ifndef MEMORY_MANAGER_UTILS_H
#define MEMORY_MANAGER_UTILS_H

#include <sys/wait.h>

/* Create exactly 2 CHILDRENS with properly COMMAND LINE ARGUMENTS */
void mmu_create_childrens(pid_t *child_pid, const int q_block_size, const int max);

#endif