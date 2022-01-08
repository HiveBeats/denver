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

    buffer = strcpy(buffer, source);

    return buffer;
}

#define LINE_MAX_LENGTH 1024

envar_t** read_env_variables(FILE* fp, int count)
{
    envar_t** array = (envar_t**)malloc(sizeof(envar_t*) * count);

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
                
                var->name = strdup(strtok(cline, delim));
                var->value = malloc(sizeof(char) * strlen(cline));
                sprintf(var->value, "%s", cline+strlen(var->name) + 1);

                //printf("%s : %s \n", var->name, var->value);
                array[j++] = var;

                free(cline);
            }
        }
    }
    return array;
}

env_arr_t get_env_variables(const char* filename)
{
    FILE* fp = fopen(filename, "r");

    env_arr_t result;
    if (fp == NULL)
    {
        //stderr
        return result;
    }

    result.count = get_variables_count(fp);
    result.array = read_env_variables(fp, result.count);

    fclose(fp);

    return result;
}



#endif