#ifndef FLIB_H
#define FLIB_H

void error(char *, int, int);

int gfile(char **buf, const char *src);
void wfile(int len, char *buf, const char *target);

struct Stack;
struct Stack *createStack(unsigned capacity);
int s_isFull(struct Stack *stack);
int s_isEmpty(struct Stack *stack);
int s_push(struct Stack *stack, int item);
int s_pop(struct Stack *stack);
int s_top(struct Stack *stack);

#endif