#ifndef PARSER_H_
#define PARSER_H_

#include <stdlib.h>
#include "list.h"

typedef struct {
    char* name;
    size_t start;
    size_t end;
} t_token;

t_list* parse_tokens(const char* string);


#endif