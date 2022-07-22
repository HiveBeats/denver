#include "parser.h"
#include "stack.h"
#include <string.h>

t_token* create_token(size_t start, size_t end) {
    t_token* token = (t_token*)malloc(sizeof(t_token));

    token->start = start;
    token->end = end;

    return token;
}

t_list* parse_tokens(const char* string) {
    t_list* result = NULL;
    t_stack* stack = stack_init();
    for (size_t i = 0; i < strlen(string); i++) {
        if (string[i] == '{') {
            stack_push(stack, i);
        } else if (string[i] == '}') {
            size_t left_p = (size_t)stack_pop(stack);

            // Length of substring
            int len = i - 1 - left_p;

            t_token* token = create_token(left_p, i);
            // todo: try to avoid double-copy
            char* buffer = malloc(sizeof(char) * len);
            strncpy(buffer, string + left_p + 1, len);
            buffer[len] = '\0';
            token->name = strdup(buffer);
            if (result == NULL) {
                result = list_init_w((void*)token);
            } else {
                list_add(result, token);
            }
        }
    }

    stack_clear(stack);

    return result;
}