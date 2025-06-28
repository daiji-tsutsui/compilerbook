#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "./print.h"
#include "./token.h"

int expect_number(Token* token);

int main(int argc, char **argv) {
    if (argc != 2) {
        error("引数の個数が正しくありません");
    }

    Token *p_token = tokenize(argv[1]);

    print_prefix();
    print_first_term(expect_number(p_token));

    print_return();
    return 0;
}

int expect_number(Token* token) {
    if (token->kind != TK_NUMBER) error("Not a number!!");

    int val = token->val;
    token = token->next;
    return val;
}
