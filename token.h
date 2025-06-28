#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "./error.h"

bool is_operator(char c);

typedef enum {
    TK_OPERATOR,
    TK_NUMBER,
    TK_EOF,
} TokenKind;

typedef struct Token Token;

struct Token {
    TokenKind kind;
    Token *next;
    int val;
    char *str;
};

Token *new_token(TokenKind kind, Token *parent, char *str) {
    Token *t = calloc(1, sizeof(Token));
    t->kind = kind;
    t->str = str;
    parent->next = t;
    return t;
}

Token *tokenize(char *p) {
    Token head;
    head.next = NULL;
    Token *current = &head;

    while (*p) {
        // skip spaces
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (is_operator(*p)) {
            current = new_token(TK_OPERATOR, current, p);
            p++;
        }

        if (isdigit(*p)) {
            current = new_token(TK_NUMBER, current, p);
            current->val = strtol(p, &p, 10);
            continue;
        }

        error("トークナイズできません");
    }

    return head.next;
}

bool is_operator(char c) {
    if (c == '+') return true;
    if (c == '-') return true;

    return false;
}
