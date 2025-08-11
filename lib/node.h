#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "./token.h"

bool DEBUG = true;
Token* TOKEN; // token stream

typedef enum {
    ND_ADD,
    ND_SUB,
    ND_MUL,
    ND_DIV,
    ND_NUM,
} NodeKind;

typedef struct Node Node;

struct Node {
    NodeKind kind;
    Node* lhs;
    Node* rhs;
    int val;
};

Node* expr();
Node* mul();
Node* primary();
bool consume(char op);
int get_number();
void print_debug();

void setup_token_stream(char* input) {
    TOKEN = tokenize(input);
}

Node* new_node(NodeKind kind, Node* lhs, Node* rhs) {
    Node* node = calloc(1, sizeof(Node));
    node->kind = kind;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node* new_node_num(int val) {
    Node* node = calloc(1, sizeof(Node));
    node->kind = ND_NUM;
    node->val = val;
    return node;
}

Node* expr() {
    if (DEBUG) printf("expr ->\n");
    Node* node = mul();

    while(true) {
        if (consume('+')) {
            Node* rhs = mul();
            node = new_node(ND_ADD, node, rhs);
        } else if (consume('-')) {
            Node* rhs = mul();
            node = new_node(ND_SUB, node, rhs);
        } else {
            return node;
        }
    }
}

Node* mul() {
    if (DEBUG) printf("mul ->\n");
    Node* node = primary();

    while(true) {
        if (consume('*')) {
            Node* rhs = primary();
            node = new_node(ND_MUL, node, rhs);
        } else if (consume('/')) {
            Node* rhs = primary();
            node = new_node(ND_DIV, node, rhs);
        } else {
            return node;
        }
    }
}

Node* primary() {
    if (DEBUG) printf("primary ->\n");
    if (consume('(')) {
        Node* node = expr();
        if (consume(')')) return node;

        error_at(TOKEN->str, "Cannot find a token ')'!!");
    }

    return new_node_num(get_number());
}

bool consume(char op) {
    if (TOKEN->kind != TK_OPERATOR || *TOKEN->str != op) return false;

    if (DEBUG) print_debug();
    TOKEN = TOKEN->next;
    return true;
}

int get_number() {
    if (DEBUG) print_debug();
    if (TOKEN->kind != TK_NUMBER) error_at(TOKEN->str, "Not a number!!");

    int val = TOKEN->val;
    TOKEN = TOKEN->next;
    return val;
}

void print_debug() {
    printf("kind: %d\n", TOKEN->kind);
    printf("  str: %c\n", *TOKEN->str);
    printf("  val: %d\n", TOKEN->val);
}
