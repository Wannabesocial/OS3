#include "config.h"
#include "ipc.h"

// PM1, PM2
const char *const TRACE_FILE[] = {"config/gcc.trace", "config/bzip.trace"};

void cf_read(_trace *traces, const int max_traces, FILE *file){

    // Init the BUFFER
    for(int i = 0; i < SHARED_BUFF_SIZE; i++){
        traces[i].logical_address = NO_DATA;
    }

    // Read file
    for(int i = 0; i < max_traces; i++){

        fscanf(file, "%x %c", &traces[i].logical_address, &traces[i].operation);
        traces[i].logical_address = traces[i].logical_address >> OFFSET_BITS;
    }
}

int cf_rows(FILE *file){

    int size;

    fseek(file, 0, SEEK_END);
    size = ftell(file) / TRACE_FILE_ROW_SIZE;
    fseek(file, 0, SEEK_SET);

    return size;
}
