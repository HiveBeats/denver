#include "template.h"
#include "processor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEF_BUFFER_SIZE 256
#define DEF_BUFFER_DELTA 100

static char* fill_file_buffer(FILE* fp) {
    int d_size = DEF_BUFFER_SIZE;
    int i = 0;
    char* buffer = malloc(d_size);
    if (buffer == NULL) {
        fprintf(stderr, "Can't allocate memory!\n");
        exit(1);
    }

    while (!feof(fp)) {
        if (i > d_size - 1) {
            d_size += DEF_BUFFER_DELTA;
            buffer = (char*)realloc(buffer, d_size);
            if (buffer == NULL) {
                fprintf(stderr, "Can't allocate memory!\n");
                exit(1);
            }
        }
        buffer[i] = (char)fgetc(fp);
        i++;
    }
    buffer[i - 1] = '\0';

    char* result = strdup(buffer);
    if (result == NULL) {
        fprintf(stderr, "Can't allocate memory!\n");
        exit(1);
    }

    free(buffer);

    return result;
}

static void overwrite_file_content(FILE* fp, const char* content) {
    int i = 0;
    fseek(fp, 0, SEEK_SET);

    while (content[i] != '\0') {
        putc(content[i], fp);
        i++;
    }
}

void process_template(const char* filename, env_arr_t variables) {
    FILE* fp = fopen(filename, "r+");
    if (fp == NULL) {
        fprintf(stderr, "Can't open template file!\n");
        exit(1);
    }

    // read file
    char* fstring = fill_file_buffer(fp);
    // process
    char* pstring = process_source(variables, strdup(fstring));
    // write
    fclose(fp);

    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr,
                "Can't open template file (again), may be it's busy!\n");
        exit(1);
    } else {
        overwrite_file_content(f, pstring);
        fclose(f);
    }

    free(pstring);
    free(fstring);
}
