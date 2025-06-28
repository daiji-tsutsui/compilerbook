#include <stdio.h>
#include <stdlib.h>

void print_prefix() {
    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
}

void print_first_term(int num) {
    printf("  mov rax, %d\n", num);
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
