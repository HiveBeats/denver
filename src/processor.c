#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "processor.h"

char* process_line(env_arr_t variables, const char* line)
{
    int i = 0, start_idx = 0, end_idx = 0, found = 0;
    int new_len = strlen(line);
    char* result = (char*)malloc(new_len);
    if (result == NULL)
    {
        fprintf(stderr, "Can't allocate memory!\n");
        exit(1);
    }

    while(line[i] != '\0') //todo:use strchrnul instead of interating
    /* http://all-ht.ru/inf/prog/c/func/strchrnul.html */
    {   
        //ищем старт темплейта
        if (line[i] == '$' && line[i+1] == '{')
        {
            start_idx = i;
            //нашли конец темплейта
            while (line[i] != '}') {
                i++;
            }
            end_idx = i;
            
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
                name[ndx] = line[j];
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
            int right_len = strlen(line + end_idx + 1);
            int mid_len = strlen(env_value);

            if (found != 0) 
            {
                int size = start_idx + mid_len + right_len + 1;
                if (size > new_len)
                {
                    new_len = size;
                    result = (char *)realloc(result, size);
                    if (result == NULL)
                    {
                        fprintf(stderr, "Can't allocate memory!\n");
                        exit(1);
                    }
                }
                
                char* lbuff = (char*)malloc(start_idx + 1);
                if (lbuff == NULL)
                {
                    fprintf(stderr, "Can't allocate memory!\n");
                    exit(1);
                }
                strncpy(lbuff, result, start_idx);

                char* buffer = (char*)malloc(size);
                if (buffer == NULL)
                {
                    fprintf(stderr, "Can't allocate memory!\n");
                    exit(1);
                }
                sprintf(buffer, "%s%s%s", lbuff, env_value, line + end_idx + 1);
                
                result = strdup(buffer);
                if (result == NULL)
                {
                    fprintf(stderr, "Can't allocate memory!\n");
                    exit(1);
                }
                free(buffer);
                free(lbuff);
            }
            else
            {
                found = 1;
                char* buffer = (char*)malloc(start_idx + 1);
                if (buffer == NULL)
                {
                    fprintf(stderr, "Can't allocate memory!\n");
                    exit(1);
                }

                strncpy(buffer, line, start_idx);
                sprintf(result, "%s%s%s", buffer, env_value, line + end_idx + 1);
                
                free(buffer);

                line = result;//todo: instead of that need to try a recursive solution
            }

            free(name);
        }
        i++;
    }
    return result;
}
