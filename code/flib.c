#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "flib.h"

void error(char *message, int do_exit, int exit_code) {
    fprintf(stderr, message);
    if (do_exit) exit(exit_code);
}

int gfile(char **buf, const char *src) {
    FILE *fp;
    long len;
    fp = fopen(src, "r");
    if (fp == NULL) error("Failed Opening File", 1, 1);
    if (fseek(fp, 0L, SEEK_END)) error("Failed Moving File Pointer", 1, 2);
    len = ftell(fp);
    if (len == -1L) error("Failed Telling File Length", 1, 2);
    if (fseek(fp, 0L, SEEK_SET)) error("Failed Reseting File Pointer", 1, 2);
    *buf = (char *)calloc(len, sizeof(char));
    if (*buf == NULL) error("Failed Allocating String", 1, 2);
    if (fread(*buf, sizeof(char), len, fp) != len)
        error("Failed Reading File", 1, 1);
    if (fclose(fp) == EOF) error("Failed Closing File", 1, 2);
    return len;
}

void wfile(int len, char *buf, const char *target) {
    FILE *fp;
    fp = fopen(target, "w");
    if (fp == NULL) error("Failed Opening File", 1, 1);
    if (fwrite(buf, sizeof(char), len, fp) != len)
        error("Failed Writing File", 1, 1);
    if (fclose(fp) == EOF) error("Failed Closing File", 1, 2);
    return;
}

struct Stack {
    int topval;
    unsigned capacity;
    int *array;
};

struct Stack *createStack(unsigned capacity) {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->topval = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

int s_isFull(struct Stack *stack) {
    return stack->topval == stack->capacity - 1;
}

int s_isEmpty(struct Stack *stack) { return stack->topval == -1; }

int s_push(struct Stack *stack, int item) {
    if (s_isFull(stack)) return INT_MIN;
    stack->array[++stack->topval] = item;
    printf("%d pushed to stack\n", item);
}

int s_pop(struct Stack *stack) {
    if (s_isEmpty(stack)) return INT_MIN;
    return stack->array[stack->topval--];
}

int s_top(struct Stack *stack) {
    if (s_isEmpty(stack)) return INT_MIN;
    return stack->array[stack->topval];
}
