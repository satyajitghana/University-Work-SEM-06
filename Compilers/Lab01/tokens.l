%{
#include <iostream>

extern int vowel_cnt;
extern int consonant_cnt;
  
void yyerror(const char *s);

%}

%option noyywrap

%%

[aeiouAEIOU]            { std::cout << "[VOWEL]"; vowel_cnt++; } 
[a-zA-Z]                { std::cout << "[CONSONANT]"; consonant_cnt++; }
\n                      { /*std::cout << "[NEWLINE]\n"; */
                        std::cout << "\nFound " << vowel_cnt << " Vowels and " << consonant_cnt << " Consonants"
                        << "\n"; vowel_cnt = 0; consonant_cnt = 0; }
.                       { std::cout << "[UNRECOGNIZED]"; }

%%