#include "processor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* concatn_things(const char* attach1, const char* attach2, const char* attach3) {
    size_t sum_size = strlen(attach1) + strlen(attach2) + strlen(attach3) + 1;

    char* buffer = (char*)malloc(sum_size);
    if (buffer == NULL) {
        fprintf(stderr, "Can't allocate memory!\n");
        exit(1);
    }
    sprintf(buffer, "%s%s%s", attach1, attach2, attach3);

    return buffer;
}

char* process_source(env_arr_t variables, const char* source) {
    int start_idx = 0;
    int end_idx = 0;

    //search for a token
    char* sign = strchr(source, '$');
    if (sign != NULL && sign[1] == '{') {
        start_idx = (int)(sign - source);

        char* csign = strchr(sign, '}');
        if (csign == NULL) {
            fprintf(stderr, "Unclosed template found on index: %d\n",
                    start_idx);
            exit(1);
        }
        end_idx = (int)(csign - source);

        //get template variable name
        char* name;
        name = (char*)malloc(sizeof(char) * ((end_idx - start_idx + 2) + 1));
        if (name == NULL) {
            fprintf(stderr, "Can't allocate memory!\n");
            exit(1);
        }

        int ndx = 0;
        for (int j = start_idx + 2; j < end_idx; j++) {
            name[ndx] = source[j];
            ndx++;
        }
        name[ndx] = '\0';

        //find environment variable value
        env_t* env = find_env(variables, name);
        if (env == NULL) {
            fprintf(stderr, "Env variable %s not found.", name);
            exit(1);
        }
        char* env_value = env->value;

        //concat string for that template variable
        char* buffer = (char*)malloc(start_idx + 1);
        if (buffer == NULL) {
            fprintf(stderr, "Can't allocate memory!\n");
            exit(1);
        }

        strncpy(buffer, source, start_idx);
        char* result = concatn_things(buffer, env_value, source + end_idx + 1);

        free(buffer);
        free(name);

        //search and process for next token
        return process_source(variables, result);
    }
    
    //return if no token is found
    return (char*)source;
}
