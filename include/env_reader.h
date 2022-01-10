#ifndef ENV_READER_H_
#define ENV_READER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct env_var
{
    char* name;
    char* value;
} envar_t;

typedef struct env_arr
{
    envar_t** array;
    int count;
} env_arr_t;

void free_env_var(envar_t* var)
{
    free(var->name);
    free(var->value);
}

void free_env(envar_t* vars[], int count)
{
    for (size_t i = 0; i < count; i++)
    {
        free_env_var(vars[i]);
    }
}

int get_variables_count(FILE* fp)
{
    int count = 0;
    if (fp != NULL)
    {
        char ch;
        while(!feof(fp))
        {
            ch = fgetc(fp);
            if(ch == '\n')
            {
                count++;
            }
        }
        fseek(fp, 0, SEEK_SET);
    }

    return count;
}

char* cut_to_end(char* source)
{
    int len = strlen(source);

    char* buffer = malloc(sizeof(char) * len);
    if (buffer == NULL)
    {
        fprintf(stderr, "Can't allocate memory!\n");
        exit(1);
    }
    buffer = strcpy(buffer, source);

    return buffer;
}

void cut_newline(char* source)
{
    int i = 0;
    while(source[i] != '\n')
    {
        i++;
    }

    if (source[i + 1] == '\0')
    {
        source[i] = source[i+1];
    }
}

#define LINE_MAX_LENGTH 1024

envar_t** read_env_variables(FILE* fp, int count)
{
    if (count <= 0)
    {
        fprintf(stderr, "Env variables not exists?\n");
        exit(1);
    }

    envar_t** array = (envar_t**)malloc(sizeof(envar_t*) * count);
    if (array == NULL)
    {
        fprintf(stderr, "Can't allocate memory!\n");
        exit(1);
    }

    const char* delim = "=";
    char *token;
    int i, j = 0;
    char line[LINE_MAX_LENGTH];
    
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            if (fgets(line, sizeof(line), fp)) 
            {
                char* cline = cut_to_end(&line);
                envar_t* var = (envar_t*)malloc(sizeof(envar_t));
                if (var == NULL)
                {
                    fprintf(stderr, "Can't allocate memory!\n");
                    exit(1);
                }

                var->name = strdup(strtok(cline, delim));
                if (var->name == NULL)
                {
                    fprintf(stderr, "Can't allocate memory!\n");
                    exit(1);
                }
                var->value = malloc(sizeof(char) * strlen(cline));
                if (var->value == NULL)
                {
                    fprintf(stderr, "Can't allocate memory!\n");
                    exit(1);
                }

                sprintf(var->value, "%s", cline+strlen(var->name) + 1);
                cut_newline(var->value);
                array[j++] = var;

                free(cline);
            }
        }
    }
    return array;
}

env_arr_t get_env_variables(const char* filename)
{
    env_arr_t result;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open env file\n");
        exit(1);
    }

    result.count = get_variables_count(fp);
    result.array = read_env_variables(fp, result.count);

    fclose(fp);

    return result;
}



#endif
