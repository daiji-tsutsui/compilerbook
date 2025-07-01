#include <stdio.h>
#include <stdlib.h>
#include "lib/print.h"
#include "lib/token.h"

bool DEBUG = false;

int get_number();
bool consume(char op);
bool at_eof();
void print_debug();

Token* token; // token stream

int main(int argc, char **argv) {
    if (argc != 2) {
        error("引数の個数が正しくありません");
    }

    USER_INPUT = argv[1];
    token = tokenize(USER_INPUT);

    print_prefix();
    print_first_term(get_number());

    while (!at_eof()) {
        if (DEBUG) {
            print_debug();
            token = token->next;
            continue;
        }

        if (consume('+')) {
            print_add_term(get_number());
            continue;
        }

        if (consume('-')) {
            print_sub_term(get_number());
            continue;
        }

        error_at(token->str, "Unexpected token: %c", token->str);
    }

    print_return();
    return 0;
}

int get_number() {
    if (token->kind != TK_NUMBER) error_at(token->str, "Not a number!!");

    int val = token->val;
    token = token->next;
    return val;
}

bool consume(char op) {
    if (token->kind != TK_OPERATOR || *token->str != op) return false;

    token = token->next;
    return true;
}

bool at_eof() {
    return (token->kind == TK_EOF);
}

void print_debug() {
    printf("kind: %d\n", token->kind);
    printf("  str: %c\n", *token->str);
    printf("  val: %d\n", token->val);
}
