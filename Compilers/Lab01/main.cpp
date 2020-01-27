#include <iostream>

int vowel_cnt = 0;
int consonant_cnt = 0;

extern int yylex();

int main(int argc, char* argv[]) {
    std::cout << "Enter your stream of characters"
              << "\n";
    yylex();
    std::cout << "Found " << vowel_cnt << " Vowels and " << consonant_cnt << " Consonants"
              << "\n";

    return 0;
}
