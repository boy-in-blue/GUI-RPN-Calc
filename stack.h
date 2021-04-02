#ifndef __stack_h__
#define __stack_h__

struct Stack* create_stack(unsigned);
int is_full(struct Stack*);
int is_empty(struct Stack*);
void push(struct Stack*, int);
int pop(struct Stack*);
int get_top(struct Stack*);

#endif
