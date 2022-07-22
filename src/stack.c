//---------------------------------------------------------------
// File: Code126_Stack.c
// Purpose: Implementation file for a demonstration of a stack
//		implemented as a linked structure.  Data type: element
// Programming Language: C
// Author: Dr. Rick Coleman
// Date: January 21, 2002
//---------------------------------------------------------------
#include "stack.h"
#include <stdlib.h> // To get access to malloc()

//--------------------------------------------
// Function: stack_init()
// Purpose: Initialize stack to empty. Use only
//		with a new stack.
// Precondition: Stack must not contain any
//		nodes.
// Returns: void
//--------------------------------------------
t_stack* stack_init() {
    t_stack* res = (t_stack*)malloc(sizeof(t_stack));
    res->top = NULL;

    return res;
}

//--------------------------------------------
// Function: stack_clear()
// Purpose: Remove all items from the stack
// Returns: void
//--------------------------------------------
void stack_clear(t_stack* stack) {
    if (!stack_is_empty(stack)) {
        struct t_item* temp = stack->top;

        // Scan stack and free all nodes
        while (stack->top != NULL) {
            temp = stack->top;
            stack->top = stack->top->next;
            free(temp);
        }
    }
}

//--------------------------------------------
// Function: stack_push()
// Purpose: stack_push an item onto the stack.
// Returns: TRUE if stack_push was successful
//		or FALSE if the stack_push failed.
//--------------------------------------------
int stack_push(t_stack* stack, stack_data data) {
    // Create a new node and insert the data
    struct t_item* node = (struct t_item*)malloc(sizeof(struct t_item));
    // Check to see if memory allocation failed
    if (node == NULL)
        return FALSE;
    // If all OK then insert the data
    node->data = data;
    node->next = NULL; // Very important to init this to NULL

    // Check to see if the stack is empty
    if (stack_is_empty(stack)) {
        // stack_push new node as first in the stack
        stack->top = node;
    } else {
        // stack_push on top of the stack
        node->next = stack->top;
        stack->top = node;
    }
    return TRUE; // Signal successful stack_push
}

//--------------------------------------------
// Function: stack_pop()
// Purpose: stack_pop an item from the Stack.
// Returns: TRUE if stack_pop was successful
//		or FALSE if the stack_pop failed.
//--------------------------------------------
stack_data stack_pop(t_stack* stack) {
    // Check for empty stack
    if (stack_is_empty(stack))
        return NULL; // Return null element if empty

    // Remove the top item from the stack
    struct t_item* temp = stack->top;
    stack->top = stack->top->next;

    // Copy the data from the top item for return
    stack_data data = temp->data;

    // Free the removed node
    free(temp);

    // Return the stack_popped element
    return data;
}

//--------------------------------------------
// Function: stack_is_empty()
// Purpose: Return true if the stack is empty
// Returns: TRUE if empty, otherwise FALSE
// Note: C has no boolean data type so we use
//	the defined int values for TRUE and FALSE
//	instead.
//--------------------------------------------
int stack_is_empty(t_stack* stack) { return (stack->top == NULL); }
