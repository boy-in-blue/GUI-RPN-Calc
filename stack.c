#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "stack.h"

struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* create_stack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int is_full(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

int is_empty(struct Stack* stack)
{
    return stack->top == -1;
}

void push(struct Stack* stack, int item)
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

int pop(struct Stack* stack)
{
    if (is_empty(stack))
    {
        printf("Stack is empty\n");
        return INT_MIN;
    }
    else
    {
        return stack->array[stack->top--];
    }
}

int get_top(struct Stack* stack)
{
    return stack->top;
}

