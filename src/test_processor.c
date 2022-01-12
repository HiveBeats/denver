#include "env_reader.h"
#include "processor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define DEF_BUFFER_SIZE 256
#define DEF_BUFFER_DELTA 100

env_t* create_env(char* name, char* value) {
    env_t* var = (env_t*)malloc(sizeof(env_t));
    if (var == NULL) {
        fprintf(stderr, "Can't allocate memory!\n");
        exit(1);
    }
    var->name = name;
    var->value = value;

    return var;
}

env_arr_t create_env_array() {
    env_arr_t result;

    env_t** array = (env_t**)malloc(sizeof(env_t*) * 2);
    if (array == NULL) {
        fprintf(stderr, "Can't allocate memory!\n");
        exit(1);
    }
    array[0] = create_env("MYSQL_DATABASE", "test");
    array[1] =
        create_env("MYSQL_ROOT_PASSWORD", "passwordpasswordpasssomethinglong");

    result.array = array;
    result.count = 2;

    return result;
}

char* parse_file(FILE* fp) {
    int d_size = DEF_BUFFER_SIZE;
    int i = 0;
    char* buffer = (char*)malloc(d_size);
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

char* read_template_file() {
    FILE* fp = fopen("./test/template.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open template file!\n");
        exit(1);
    }

    return parse_file(fp);
}

char* read_reference_output_file() {
    FILE* fp = fopen("./test/output.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open output file!\n");
        exit(1);
    }

    return parse_file(fp);
}

void assert_fail(char* source) {
    fprintf(stderr, "Processing test [ " RED "FAILED" RESET " ]\n");
    fprintf(stderr, "Failed string:\n%s\n", source);
}

void assert_success() {
    fprintf(stderr, "Processing test [ " GREEN "PASSED" RESET " ]\n");
}

int main(void) {
    // create env array
    env_arr_t array = create_env_array();

    // read template file
    char* template = read_template_file();

    // process
    char* output = process_source(array, template);

    // read reference output file
    char* reference_output = read_reference_output_file();

    // compare
    int result = strcmp(output, reference_output);

    // assert
    if (result != 0) {
        assert_fail(output);
        exit(1);
    } else {
        assert_success();
    }

    return 0;
}
