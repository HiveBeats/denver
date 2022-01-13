#include "env_reader.h"
#include "template.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define VER "0.0.1"
#define YEAR 2021
#define AUTHOR "HiveBeats"

void print_help() {
    printf("Fill template strings in your files with .env -formatted "
           "values.\nUsage:\n");
    printf("  denver [-e <arg>...] [-t <arg>...]\n");
    printf("  denver -h\nOptions:\n");
    printf("  -e FILE                Specify a path to a .env file (can be "
           "named differently)\n"
           "                           ex: ./test/.env\n");
    printf("  -t FILE                Specify a path to a template file (can be "
           "named differently)\n"
           "                           ex: ./test/template.txt\n");
}

void print_ver() {
    printf("denver %s\n", VER);
    printf("Copyright (C) %d %s\n", YEAR, AUTHOR);
    printf("License MIT\nThis is free software: you are free to change and "
           "redistribute it.\n");
    printf(
        "The software is provided \"as is\", without warranty of any kind.\n");
}

int parse_args(int argc, char* argv[], char** env, char** template) {
    int is_exit = 0;
    int opt;
    while ((opt = getopt(argc, argv, "e:t:vh")) != -1) {
        switch (opt) {
            case 'v':
                print_ver();
                is_exit = 1;
                break;
            case 'h':
                print_help();
                is_exit = 1;
                break;
            case 'e':
                *env = strdup(optarg);
                break;
            case 't':
                *template = strdup(optarg);
                break;
            case '?':
                fprintf(stderr, "unknown option: %c\n", optopt);
                break;
            default:
                break;
        }
    }
    return is_exit;
}

int main(int argc, char* argv[]) {
    char* env_filename = NULL;
    char* tmp_filename = NULL;

    int ext = parse_args(argc, argv, &env_filename, &tmp_filename);
    if (env_filename == NULL || tmp_filename == NULL) {
        if (ext) {
            exit(0);
        } else {
            fprintf(stderr, "Please, provide .env and template file path's\n");
            exit(1);
        }
    }

    env_arr_t envs = get_env_variables(env_filename);

    process_template(tmp_filename, envs);

    free_env(envs.array, envs.count);
    free(envs.array);
    free(env_filename);
    free(tmp_filename);

    return 0;
}
