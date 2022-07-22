#ifndef LIST_H
#define LIST_H

typedef struct {
    void* data;
    struct t_list* next;
} t_list;

t_list* list_init();
t_list* list_add(t_list* list, void* item);
t_list* list_clear(t_list* list);
t_list* list_is_empty(t_list* list);

#endif