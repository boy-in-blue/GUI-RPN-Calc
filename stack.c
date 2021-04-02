#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "stack.h"

struct Stack
{
    int top;
    unsigned capacity;
    int *array;
};

struct Stack *create_stack(unsigned capacity)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    for (int i = 0; i < capacity; i++)
    {
        stack->array[i] = 0;
    }
    return stack;
}

int *get_all_values(struct Stack *stack)
{
    return stack->array;
}

int is_full(struct Stack *stack)
{
    return stack->top == stack->capacity - 1;
}

int is_empty(struct Stack *stack)
{
    return stack->top == -1;
}

void push(struct Stack *stack, int item)
{
    if (is_full(stack))
    {
        printf("Stack is full\n");
        return;
    }
    else
    {
        stack->array[++stack->top] = item;
        printf("%d pushed to the top of the stack\n", item);
    }
}

int pop(struct Stack *stack)
{
    int rv;
    if (is_empty(stack))
    {
        printf("Stack is empty\n");
        return INT_MIN;
    }
    else
    {
        rv = stack->array[stack->top];
        stack->array[stack->top] = 0;
        stack->top--;
        return rv;
    }
}

int get_top(struct Stack *stack)
{
    return stack->top;
}
