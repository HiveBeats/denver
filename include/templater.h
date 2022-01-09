#ifndef TEMPLATER_H_
#define TEMPLATER_H_

#include "env_reader.h"

envar_t* find_env(env_arr_t variables, const char* name)
{
    for (int i = 0; i < variables.count; i++)
    {
        if (strcmp(name,variables.array[i]->name) == 0) 
        {
            return variables.array[i];
        }
    }
}

char* process_line(env_arr_t variables, const char* line)
{
    char chr;
    int i=0; 
    int start_idx =0; 
    int end_idx = 0;
    int found = 0;
    int init_len = strlen(line);
    int new_len = init_len;
    char* result = malloc(init_len);

    
    while(line[i] != '\0')
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
            name = malloc(sizeof(char) * ((end_idx - start_idx+2) + 1));
            int ndx = 0;
            for (int j = start_idx + 2; j < end_idx; j++)
            {
                name[ndx] = line[j];
                ndx++;
            }
            name[ndx]='\0';
            //получили значение на замену темплейту
            envar_t* env = find_env(variables, name);
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
                }
                
                char* lbuff = malloc(start_idx + 1);
                strncpy(lbuff, result, start_idx);

                char* buffer = malloc(size);
                sprintf(buffer, "%s%s%s", lbuff, env_value, line + end_idx + 1);
                
                result = strdup(buffer);
                free(buffer);
                free(lbuff);
            }
            else
            {
                found = 1;
                char* buffer = malloc(start_idx + 1);
                strncpy(buffer, line, start_idx);
                sprintf(result, "%s%s%s", buffer, env_value, line + end_idx + 1);
                
                free(buffer);

                line = result;
            }

            free(name);
        }
        i++;
    }
    return result;
}

char* fill_file_buffer(FILE* fp)
{
    int d_size = 1024;
    int i = 0;
    char* buffer = malloc(d_size);
    while (!feof(fp))
    {
        if (i > d_size - 1)
        {
            d_size += 100;
            buffer = realloc(buffer, d_size);
        }
        buffer[i] = fgetc(fp);
        i++;
    }
    buffer[i-1] = '\0';

    char* result = strdup(buffer);
    free(buffer);

    return result;
}

void overwrite_file_content(FILE* fp, char* content)
{
    int i = 0;
    fseek(fp, 0, SEEK_SET);
    
    while(content[i] != '\0')
    {
        putc(content[i], fp);
        i++;
    }
}

void process_template(const char* filename, env_arr_t variables)
{
    FILE* fp = fopen(filename, "r+");
    if (fp != NULL)
    {
        //read file
        char* fstring = fill_file_buffer(fp);
        //process
        char* pstring = process_line(variables, strdup(fstring));
        //write
        fclose(fp);
        
        
        FILE* f = fopen(filename, "w");
        if (f != NULL)
        {
            overwrite_file_content(f, pstring);
            fclose(f);
        }

        free(pstring);
        free(fstring);
    }

    fclose(fp);
}

#endif