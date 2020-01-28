%{
#include <iostream>

extern int vowel_cnt;
extern int consonant_cnt;
  
void yyerror(const char *s);

%}

%option noyywrap

%%

[aeiouAEIOU]            { std::cout << "[VOWEL: " << yytext << "]"; vowel_cnt++; } 
[a-zA-Z]                { std::cout << "[CONSONANT: " << yytext << "]"; consonant_cnt++; }
\n                      { std::cout << "\nEND PARSE [NEWLINE]\n\n"; return 1; }
.                       { std::cout << "[UNRECOGNIZED: "<< yytext << " ]"; }

%%