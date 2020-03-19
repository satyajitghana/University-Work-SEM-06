#include <iostream>

extern int yylex();

int dposcnt = 0, dnegcnt = 0, fposcnt = 0, fnegcnt = 0;

auto main(int argc, char* argv[]) -> int {
    std::cout << "enter different numbers" << '\n';

    if (yylex() == 0)
        std::cout << "\nparsed successfully" << '\n';
    else
        std::cerr << "error parsing" << '\n';

    std::cout << '\n';

    std::cout << "Positive Decimals : " << dposcnt << '\n'
              << "Negative Decimals : " << dnegcnt << '\n'
              << "Positive Fractions : " << fposcnt << '\n'
              << "Negative Fractions : " << fnegcnt << '\n';

    return 0;
}