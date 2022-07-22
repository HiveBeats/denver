#include "processor.h"
#include "parser.h"
#include "sb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* process_source(env_arr_t variables, const char* source) {
    t_list* tokens = parse_tokens(source);
    t_list* current = tokens;

    StringBuilder* sb = sb_create();
    size_t p = 0;

    while (!list_is_empty(current)) {
        t_token* token = (t_token*)current->data;

        size_t left = p;
        p = token->start;

        const char* substr = source + left;
        sb_appendn(sb, substr, p - left);

        sb_append(sb, token->name);
        free(token->name);

        p = token->end;
        current = current->next;
    }

    list_clear(tokens);

    char* result = sb_concat(sb);
    sb_free(sb);

    return result;
}
