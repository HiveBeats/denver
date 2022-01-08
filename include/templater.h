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

void process_template(const char* filename, env_arr_t variables)
{
    FILE* fp = fopen(filename, "rw");
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