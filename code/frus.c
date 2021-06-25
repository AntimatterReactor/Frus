#include "flib.h"
#include <stdio.h>

void interpreter(char *rawIn, int inLen) {
    struct Stack *locstk = createStack(100U);
    char pstack[30000] = {0};
    char *stkit = pstack;
    int skip = 0;
    for (size_t i = 0; i < inLen; i++) {
        if (skip > 0) {
            if (rawIn[i] == ']') skip -= 1;
            if (rawIn[i] == '[') skip += 1;
            continue;
        }

        switch (rawIn[i]) {
        case '>': stkit++; break;
        case '<': stkit--; break;
        case '+': ++*stkit; break;
        case '-': --*stkit; break;

        case '[':
            if (*stkit != 0)
                s_push(locstk, i);
            else if (*stkit == 0)
                skip += 1;
            break;

        case ']':
            if (*stkit != 0) i = s_top(locstk) - 1;
            s_pop(locstk);
            break;

        case '.': putchar(*stkit); break;
        case ',': *stkit = getchar(); break;
        }
    }
}

int main(int argc, char **argv) {
    char *buffer;
    int len;
    if (argc > 2) error("Not enough args, need file name", 1, 1);
    if (argc < 2) error("Too much args", 1, 1);
    gfile(&buffer, argv[1]);
    interpreter(buffer, len);
    free(buffer);
}