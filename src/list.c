#include "list.h"
#include "stdlib.h"

static t_list* get_last(t_list* list) {
    t_list* last = list->next;

    while (list->next != NULL) {
        last = list->next;
    }

    if (last == NULL)
        return list;

    return last;
}

static t_list* create_node(void* item) {
    t_list* node = (t_list*)malloc(sizeof(t_list));
    node->data = item;
    node->next = NULL;

    return node;
}

t_list* list_init() {
    t_list* res = (t_list*)malloc(sizeof(t_list));
    res->next = NULL;

    return res;
}

t_list* list_init_w(void* item) {
    t_list* list = list_init();
    list->data = item;

    return list;
}

void list_add(t_list* list, void* item) {
    t_list* node = create_node(item);

    t_list* last = get_last(list);
    last->next = node;
}

void list_clear(t_list* list) {
    t_list* current = list;
    t_list* next = list->next;
    do {
        free(current);

        current = next;
        next = next->next;
    } while (next != NULL);
}

int list_is_empty(t_list* list) {
    return list->next == NULL && list->data == NULL;
}
