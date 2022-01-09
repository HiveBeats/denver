#ifndef TEMPLATER_H_
#define TEMPLATER_H_

#include "env_reader.h"

envar_t* find_env(env_arr_t variables, const char* name)
{
    for (int i = 0; i < variables.count; i++)
    {
        if (strcmp(name,variables.array[i]) == 0) 
        {
            return variables.array[i];
        }
    }
}

/*
char smth[] = "CREATE USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT}';";
    
    char* en;
    char* del = "${}";
    en = strdup(strtok(smth, del));
    

    while (en != NULL) {
        printf("%s \n",en);
        en = strtok(NULL, del);
    }
    */

char* process_line(char* line)
{
    char chr;
    int i = 0;
    int start_idx, end_idx;
    
    while(chr = line[i] != '\0')
    {
        //ищем старт темплейта
        if (chr == '$' && line[i+1] == '{')
        {
            start_idx = i;
            //нашли конец темплейта
            while (chr = line[i] != '}') {
                i++
            }
            end_idx = i;
            //вытаскиваем имя темплейта
            char* name;
            name = malloc(sizeof(char) * ((end_idx - start_idx) + 1));
            int ndx = 0;
            for (int j = start_idx; j < end_idx; j++)
            {
                name[ndx] = line[j];
                ndx++;
            }
            //получили значение на замену темплейту
            envar_t* env = find_env(name);
            char* env_value = env->value;

            //конкатенируем...


            //чистимся 
            free(name);
        }
        i++;
    }
}

void process_template(const char* filename, env_arr_t variables)
{
    FILE* fp = fopen(filename, "rw");
    //для каждой строки
    //читать символы в файле
    //дойти до символа $
    //если следующий символ {, то запомнить индекс символа доллар
    //запомнить все символы до } в переменную env_name
    //найти это значение
    //от индекса отсчитать 2+ strlen(env_name) + 1
    //удалить их и заменить на  value
    fclose(fp);
}

#endif