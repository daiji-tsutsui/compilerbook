#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void error(char *fmt, ...);
void print_prefix();
void print_first_term(char** p);
void print_add_term(char** p);
void print_sub_term(char** p);
void print_return();

int main(int argc, char **argv) {
    if (argc != 2) {
        error("引数の個数が正しくありません");
    }

    char* p = argv[1];

    print_prefix();
    print_first_term(&p);

    while (*p) {
        if (*p == '+') {
            p++;
            print_add_term(&p);
            continue;
        }

        if (*p == '-') {
            p++;
            print_sub_term(&p);
            continue;
        }

        error("Unexpected character!!: '%c'", *p);
    }

    print_return();
    return 0;
}

void error(char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

void print_prefix() {
    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
}

void print_first_term(char** p) {
    printf("  mov rax, %ld\n", strtol(*p, &*p, 10));
}

void print_add_term(char** p) {
    printf("  add rax, %ld\n", strtol(*p, &*p, 10));
}

void print_sub_term(char** p) {
    printf("  sub rax, %ld\n", strtol(*p, &*p, 10));
}

void print_return() {
    printf("  ret\n");
}
