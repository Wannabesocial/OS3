/* Here we have STRUCTS and FUNCTIONS relatedto operation 
in a Config File, aka the 2 traces files */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>

#define TRACE_FILE_ROW_SIZE 11 // 11 bytes per row 

extern const char *const TRACE_FILE[];

typedef struct _trace{
    unsigned int logical_address;   // Hexadecimal
    char operation;                 // Read-Write (R-W)
}_trace;

/* --------------------------------------- */

/* Read and Save a number of traces. File must be already OPEN. REMEMBER to CLOSE it */
void cf_read(_trace *traces, const int max_traces, FILE *file);

/* Find and Return the NUmber of Rows of a Trace File */
int cf_rows(FILE *file);

#endif