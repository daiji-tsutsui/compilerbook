#include <stdio.h>
#include <stdlib.h>
#include "lib/print.h"
#include "lib/node.h"

void print_tree(Node* node);
void print_node(Node* node);

int main(int argc, char **argv) {
    if (argc != 2) {
        error("引数の個数が正しくありません");
    }

    char* input = argv[1];
    setup_error_logger(input);
    setup_token_stream(input);

    print_prefix();
    // print_first_term(get_number());

    Node* head = expr();
    print_tree(head);

    // print_return();
    return 0;
}

void print_tree(Node* node) {
    if (node->kind == ND_NUM) {
        printf("%d ", node->val);
        return;
    }
    print_node(node);

    Node* lhs = node->lhs;
    print_tree(lhs);

    Node* rhs = node->rhs;
    print_tree(rhs);
}

void print_node(Node* node) {
    if (node->kind == ND_ADD) {
        printf("+ ");
    } else if (node->kind == ND_SUB) {
        printf("- ");
    } else if (node->kind == ND_MUL) {
        printf("* ");
    } else if (node->kind == ND_DIV) {
        printf("/ ");
    }
}
