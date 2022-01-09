//env_reader.h
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>
//necessary
#include <unistd.h>
#include "env_reader.h"
#include "templater.h"

void parse_args(int argc, char* argv[], char** env, char** template)
{
    int opt;
    while ((opt = getopt(argc, argv, "e:t:")) != -1 ) 
    {
        switch (opt)
        {
            case 'e':
                *env = strdup(optarg);
                break;
            case 't':
                *template = strdup(optarg);
                break;
            case ':':
                printf("option needs a value\n");
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                break;
            default:
                break;
        }
    }
}

int main(int argc, char* argv[])
{
    int opt;
    char* env_filename;
    char* tmp_filename;
    
    parse_args(argc, argv, &env_filename, &tmp_filename);

    env_arr_t envs = get_env_variables(env_filename);
    
    process_template(tmp_filename, envs);

    free_env(envs.array, envs.count);
    free(env_filename);
    free(tmp_filename);
    
    return 0;
}