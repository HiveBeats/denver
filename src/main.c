#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "env_reader.h"
#include "template.h"

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
                fprintf(stderr, "option needs a value\n");
                break;
            case '?':
                fprintf(stderr, "unknown option: %c\n", optopt);
                break;
            default:
                break;
        }
    }
}

int main(int argc, char* argv[])
{
    int opt;
    char* env_filename = NULL;
    char* tmp_filename = NULL;
    
    parse_args(argc, argv, &env_filename, &tmp_filename);
    if (env_filename == NULL || tmp_filename == NULL)
    {
        exit(1);
    }

    env_arr_t envs = get_env_variables(env_filename);
    
    process_template(tmp_filename, envs);

    free_env(envs.array, envs.count);
    free(envs.array);
    free(env_filename);
    free(tmp_filename);
    
    return 0;
}
