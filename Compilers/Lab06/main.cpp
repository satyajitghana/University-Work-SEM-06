#include <stdio.h>

#include <iostream>

#include "lab06.tab.h"

extern int flag;
extern FILE* yyin;

auto main(int argc, char* argv[]) -> int {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
    }
    yyparse();
    if (flag == 0) {
        std::cout << "parse successful" << '\n';
    }
    return 0;
}

void yyerror(char* s) {
    std::cout << "Error Parsing: " << s << '\n';
    flag = 1;
}
