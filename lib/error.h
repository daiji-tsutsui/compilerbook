#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char* USER_INPUT = NULL;

void setup_error_logger(char* src) {
    USER_INPUT = src;
}

void error(char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

void error_at(char* err_locate, char* fmt, ...) {
    if (USER_INPUT == NULL) {
        error(fmt);
    }

    va_list ap;
    va_start(ap, fmt);

    int pos = err_locate - USER_INPUT;
    fprintf(stderr, "%s\n", USER_INPUT);
    fprintf(stderr, "%*s", pos, " ");
    fprintf(stderr, "^ ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}
