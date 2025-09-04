/* Here we have STRUCTS and FUNCTIONS related to
POSIX IPC */

#ifndef IPC_H
#define IPC_H

#include "config.h"

#include <stdbool.h>
#include <stdlib.h>
#include <semaphore.h>

#define SHARED_BUFF_SIZE 16 // MAX number of TRACE at once
#define NO_DATA 0xffffffff  // Init value for SHARED MEMORY values in array 
#define NO_CAP -1           // No MAX number of traces given 

// POTITION OF COMMAND LINE ARGUMENT
#define P_BLOCK_SIZE  0
#define P_MAX_ROWS    1
#define P_POTITION    2 // Potition in arrays of names

// SEMAPHORES and SHARED MEMORY names
#define SHARED_MEM_NAME "/shared_mem"

#define PM1_SEMAPHORE 0
#define PM2_SEMAPHORE 1
#define MM_SEMAPHORE  2 // Memory Managment SEMAPHORE potition

extern const char *const SEM_NAME[];

//extern const char *const SEM_NAME_SETUP[];  // NAMES FOR SEMAPHORES
//extern const char *const SHARED_MEM_NAME[]; // NAMES FOR SHARED MEMORY

// Macro for Error handling
#define handle_error(msg)\
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

typedef struct _shared_memory{
    _trace buffer[SHARED_BUFF_SIZE];
    bool terminate; // I can know when PM1 and PM2 end so i can terminate MM
}_shared_memory;

/* ------------------------------------------------------- */

#endif