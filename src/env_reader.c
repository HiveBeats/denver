#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "env_reader.h"

static void free_env_var(env_t* var) {
    free(var->name);
    free(var->value);
}

void free_env(env_t* vars[], int count) {
    for (size_t i = 0; i < count; i++) {
        free_env_var(vars[i]);
    }
}

static int get_variables_count(FILE* fp) {
    int count = 0;
    if (fp != NULL) {
        char ch;
        while (!feof(fp)) {
            ch = (char)fgetc(fp);
            if (ch == '\n') {
                count++;
            }
        }
        fseek(fp, 0, SEEK_SET);
    }

    return count;
}

static void cut_newline(char** source) {
    int len = (int)strlen(*source);
    int i = 0;
    while ((*source)[i] != '\n') {
        i++;
    }

    if ((*source)[i + 1] == '\0') {
        (*source)[i] = (*source)[i + 1];
        *source = (char*)realloc(*source, len);
    }
}

#define LINE_MAX_LENGTH 1024

static env_t** read_env_variables(FILE* fp, int count) {
    if (count <= 0) {
        fprintf(stderr, "Env variables not exists?\n");
        exit(1);
    }

    env_t** array = (env_t**)malloc(sizeof(env_t*) * count);
    if (array == NULL) {
        fprintf(stderr, "Can't allocate memory!\n");
        exit(1);
    }

    const char* delim = "=";
    char* token;
    int j = 0;
    char line[LINE_MAX_LENGTH];

    if (fp != NULL) {
        while (!feof(fp)) {
            if (fgets(line, sizeof(line), fp)) {
                env_t* var = (env_t*)malloc(sizeof(env_t));
                if (var == NULL) {
                    fprintf(stderr, "Can't allocate memory!\n");
                    exit(1);
                }

                var->name = strdup(strtok(line, delim));
                if (var->name == NULL) {
                    fprintf(stderr, "Can't allocate memory!\n");
                    exit(1);
                }

                char* value = line + strlen(var->name) + 1;

                var->value = malloc(sizeof(char) * strlen(value) + 1);
                if (var->value == NULL) {
                    fprintf(stderr, "Can't allocate memory!\n");
                    exit(1);
                }
                sprintf(var->value, "%s", value);
                cut_newline(&(var->value));
                array[j++] = var;
            }
        }
    }
    return array;
}

env_arr_t get_env_variables(const char* filename) {
    env_arr_t result;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open env file\n");
        exit(1);
    }

    result.count = get_variables_count(fp);
    result.array = read_env_variables(fp, result.count);

    fclose(fp);

    return result;
}

env_t* find_env(env_arr_t variables, const char* name) {
    for (int i = 0; i < variables.count; i++) {
        if (strcmp(name, variables.array[i]->name) == 0) {
            return variables.array[i];
        }
    }
    return NULL;
}
