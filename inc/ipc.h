/* Here we have STRUCTS and FUNCTIONS related to
POSIX IPC */

#ifndef IPC_H
#define IPC_H

#include <stdbool.h>
#include <stdlib.h>

#define SHARED_BUFF_SIZE 16 // MAX number of TRACE at once
#define NO_CAP -1           // No MAX number of traces given 

// POTITION OF COMMAND LINE ARGUMENT
#define P_BLOCK_SIZE    0
#define P_MAX_ROWS      1
#define P_POSIX         2 // Potition in arrays of names

// SEMAPHORES and SHARED MEMORY names
#define SHARED_MEM_NAME "shared_mem"
extern const char *const SEM_NAME[];

//extern const char *const SEM_NAME_SETUP[];  // NAMES FOR SEMAPHORES
//extern const char *const SHARED_MEM_NAME[]; // NAMES FOR SHARED MEMORY

// Macro for Error handling
#define handle_error(msg)\
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

typedef struct _shared_memory{
    bool problem;   // Page manager SET UP (success-fail)
}_shared_memory;



#endif