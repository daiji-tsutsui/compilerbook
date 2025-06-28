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

void print_add_term(int num) {
    printf("  add rax, %d\n", num);
}

void print_sub_term(int num) {
    printf("  sub rax, %d\n", num);
}

void print_return() {
    printf("  ret\n");
}
