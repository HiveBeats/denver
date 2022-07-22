#ifndef LIST_H
#define LIST_H

typedef struct t_list {
    void* data;
    struct t_list* next;
} t_list;

t_list* list_init();
t_list* list_init_w(void* item);
void list_add(t_list* list, void* item);
void list_clear(t_list* list);
int list_is_empty(t_list* list);

#endif