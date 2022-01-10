#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "processor.h"

static char* concatn_things(char* attach1, char* attach2, char* attach3)
{
    size_t sum_size = strlen(attach1) + strlen(attach2) + strlen(attach3) + 1;
    printf("%d \n", sum_size);
    char* buffer = (char*)malloc(sum_size);
    if (buffer == NULL)
    {
        fprintf(stderr, "Can't allocate memory!\n");
        exit(1);
    }
    sprintf(buffer, "%s%s%s", attach1, attach2, attach3);
    
    return buffer;
}

char* process_source(env_arr_t variables, const char* source)
{
    int start_idx = 0, end_idx = 0;
    int new_len = strlen(source);
    // char* result = (char*)malloc(new_len);
    // if (result == NULL)
    // {
    //     fprintf(stderr, "Can't allocate memory!\n");
    //     exit(1);
    // }
    //printf("%s\n", source);
    //ищем старт темплейта
    char* sign = strchr(source, '$');
    if (sign != NULL && sign[1] == '{')
    {
        start_idx = sign - source;
        char* csign = strchr(sign, '}');
        if (csign == NULL)
        {
            fprintf(stderr, "Unclosed template found on index: %d\n", start_idx);
            exit(1);
        }
        end_idx = csign - source;

        //вытаскиваем имя темплейта
        char* name;
        name = (char*)malloc(sizeof(char) * ((end_idx - start_idx+2) + 1));
        if (name == NULL)
        {
            fprintf(stderr, "Can't allocate memory!\n");
            exit(1);
        }

        int ndx = 0;
        for (int j = start_idx + 2; j < end_idx; j++)
        {
            name[ndx] = source[j];
            ndx++;
        }
        name[ndx]='\0';
        //получили значение на замену темплейту
        env_t* env = find_env(variables, name);
        if (env == NULL)
        {
            fprintf(stderr, "Env variable %s not found.", name);
            exit(1);
        }
        char* env_value = env->value;
        
        //конкатенируем...
        int right_len = strlen(source + end_idx + 1);
        int mid_len = strlen(env_value);
        
        char* buffer = (char*)malloc(start_idx + 1);
        if (buffer == NULL)
        {
            fprintf(stderr, "Can't allocate memory!\n");
            exit(1);
        }

        strncpy(buffer, source, start_idx);
        char* result = concatn_things(buffer, env_value, source + end_idx + 1);
        //sprintf(result, "%s%s%s", buffer, env_value, source + end_idx + 1);
        
        free(buffer);
        free(name);

        return process_source(variables, result);
    }
    return source;
}
