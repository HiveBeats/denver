#include "env_reader.h"
#include "template.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define VER "0.0.3"
#define YEAR 2022
#define AUTHOR "HiveBeats"
#define DEFAULT_ENV ".env"

typedef struct arg_opt
{
    char* env_name;
    char* template_name;
    int is_exit;
    int process_self;
} arg_t;

void print_help() {
    printf("Fill template strings in your files with .env -formatted "
           "values.\n\nUsage:\n");
    printf("  denver [-e <arg>...] [-t <arg>...]\n");
    printf("  denver -h\n\nOptions:\n");
    printf("  -e FILE                Specify a path to a .env file (default: "
           "./.env)\n"
           "                           ex: ./test/custom-env\n\n");
    printf("  -t FILE                Specify a path to a template file (can be "
           "named differently).\n"
           "                           ex: ./test/template.txt\n\n");
    printf("  -h                     Get helpful usage information.\n\n");
    printf("  -v                     Get current installed version.\n\n");
}

void print_ver() {
    printf("denver %s\n", VER);
    printf("Copyright (C) %d %s\n", YEAR, AUTHOR);
    printf("License MIT\nThis is free software: you are free to change and "
           "redistribute it.\n");
    printf(
        "The software is provided \"as is\", without warranty of any kind.\n");
}

arg_t parse_args(int argc, char* argv[]) {
    arg_t result = { .is_exit=0, .process_self=0 };

    int opt;
    while ((opt = getopt(argc, argv, "e:t:vhs")) != -1) {
        switch (opt) {
            case 'v':
                print_ver();
                result.is_exit = 1;
                break;
            case 'h':
                print_help();
                result.is_exit = 1;
                break;
            case 'e':
                result.env_name = strdup(optarg);
                break;
            case 't':
                result.template_name = strdup(optarg);
                break;
            case 's':
                result.process_self = 1;
                break;
            case '?':
                fprintf(stderr, "unknown option: %c\n", optopt);
                break;
            default:
                break;
        }
    }

    return result;
}

void process(char* env, char* template) {
    env_arr_t envs = get_env_variables(env);

    process_template(template, envs);

    free_env(envs.array, envs.count);
    free(envs.array);
}

int main(int argc, char* argv[]) {
    arg_t args = parse_args(argc, argv);

    if (args.is_exit) {
        exit(0);
    }

    if (args.template_name == NULL && !args.process_self) {
        fprintf(stderr, "Please, provide a template file path's\n");
        exit(1);
    }
    
    //set default env name, if needed
    if (args.env_name == NULL) {
        args.env_name = malloc(sizeof(char) * strlen(DEFAULT_ENV) + 1);
        args.env_name = strcpy(args.env_name, DEFAULT_ENV);
    }

    if (args.process_self) {
        process(args.env_name, args.env_name);
    }

    if (args.template_name != NULL) {
        process(args.env_name, args.template_name);
    }

    free(args.env_name);
    free(args.template_name);

    return 0;
}
