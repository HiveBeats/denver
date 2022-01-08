#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>
//necessary
#include <string.h>
#include <unistd.h>

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

    printf("env filename: %s\n", env_filename);
    printf("template filename: %s\n", tmp_filename);

    free(env_filename);
    free(tmp_filename);
    
    return 0;
}