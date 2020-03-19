#include <stdio.h>

#include <iostream>

extern int yylex();
extern FILE* yyin;

int charcnt = 0, wordcnt = 0, spacecnt = 0, eolcnt = 0;

auto main(int argc, char* argv[]) -> int {
    FILE* file;

    if (argc > 1) {
        file = fopen(argv[1], "r");
        yyin = file;
    }

    if (yylex() == 0)
        std::cout << "parsed successfully" << '\n';
    else
        std::cerr << "error parsing" << '\n';

    std::cout << "character count = " << charcnt << '\n'
              << "word count = " << wordcnt << '\n'
              << "space count = " << spacecnt << '\n'
              << "EOL count = " << eolcnt << '\n';

    return 0;
}