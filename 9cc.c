#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "lib/print.h"
#include "lib/token.h"

bool DEBUG = true;

int get_number(Token* token);
bool at_eof(Token token);
void print_debug(Token token);

int main(int argc, char **argv) {
    if (argc != 2) {
        error("引数の個数が正しくありません");
    }

    Token token = tokenize(argv[1]);

    print_prefix();
    print_first_term(get_number(&token));

    while (!at_eof(token)) {
        if (DEBUG) {
            print_debug(token);
            token = *token.next;
        }
    }

    print_return();
    return 0;
}

int get_number(Token* token) {
    if (token->kind != TK_NUMBER) error("Not a number!!");

    int val = token->val;
    *token = *token->next;
    return val;
}

bool at_eof(Token token) {
    return (token.kind == TK_EOF);
}

void print_debug(Token token) {
    printf("kind: %d\n", token.kind);
    printf("  str: %c\n", *token.str);
    printf("  val: %d\n", token.val);
}
