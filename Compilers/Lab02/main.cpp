#include <iostream>
#include <string>

extern int yylex();

std::string maxstring = "";

auto main(int argc, char* argv[]) -> int {

    std::cout << "enter stream of characters" << "\n";

    yylex();

    std::cout << "max string: " << maxstring << ", len: " << maxstring.length() << "\n";

    return 0;
}
