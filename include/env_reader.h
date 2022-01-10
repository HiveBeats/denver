#ifndef ENV_READER_H_
#define ENV_READER_H_

typedef struct env_var
{
    char* name;
    char* value;
} env_t;

typedef struct env_arr
{
    env_t** array;//todo: not store pointers to structs, but structs
    int count;
} env_arr_t;

void free_env(env_t* vars[], int count);
env_t* find_env(env_arr_t variables, const char* name);
env_arr_t get_env_variables(const char* filename);

#endif
