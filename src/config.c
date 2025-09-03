#include "config.h"

// PM1, PM2
const char *const TRACE_FILE[] = {"config/gcc.trace", "config/bzip.trace"};

void cf_read(_trace *traces, const int max_traces, FILE *file){

    for(int i = 0; i < max_traces; i++){

        fscanf(file, "%x %c", &traces[i].logical_address, &traces[i].operation);
    }
}

int cf_rows(FILE *file){

    int size;

    fseek(file, 0, SEEK_END);
    size = ftell(file) / TRACE_FILE_ROW_SIZE;
    fseek(file, 0, SEEK_SET);

    return size;
}
