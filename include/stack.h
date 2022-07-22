//---------------------------------------------------------------
// Implementation Author: Dr. Rick Coleman,
// (https://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code126_Stack.html)
//---------------------------------------------------------------
#ifndef STACK_H
#define STACK_H

#include <stdio.h>

typedef size_t stack_data;

// Define a structure to be used as the stack item
struct t_item {
    stack_data data;
    struct t_item* next;
};

typedef struct {
    struct t_item* top;
} t_stack;

// List Function Prototypes
t_stack* stack_init();             // Initialize the stack
void stack_clear(t_stack* stack); // Remove all items from the stack
int stack_push(t_stack* stack, stack_data data); // push an item onto the stack
stack_data stack_pop(t_stack* stack);            // pop an item from the stack
int stack_is_empty(t_stack* stack);              // check if stack is empty

// Define TRUE and FALSE if they have not already been defined
#ifndef FALSE
#define FALSE (0)
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif

#endif // End of stack header