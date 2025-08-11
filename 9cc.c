#include <stdio.h>
#include <stdlib.h>
#include "lib/print.h"
#include "lib/node.h"

// bool at_eof();
void print_debug();

int main(int argc, char **argv) {
    if (argc != 2) {
        error("引数の個数が正しくありません");
    }

    char* input = argv[1];
    setup_error_logger(input);
    setup_token_stream(input);

    print_prefix();
    // print_first_term(get_number());

    Node* node = expr();

    // error_at(TOKEN->str, "Unexpected token: %c", TOKEN->str);

    print_return();
    return 0;
}

// bool at_eof() {
//     return (token->kind == TK_EOF);
// }
