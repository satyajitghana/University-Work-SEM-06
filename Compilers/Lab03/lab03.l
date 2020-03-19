%{

#include <iostream>

extern int dposcnt, dnegcnt, fposcnt, fnegcnt;

%}

%option noyywrap

white       [ \n\t]+
digit       [0-9]
integer     [digit]+
exponent    [eE][+-]?{integer}

%%

\+?{digit}+             { std::cout << "found +ve decimal : " << yytext << '\n'; dposcnt++; }
\+?{digit}+\.{digit}*   { std::cout << "found +ve fraction : "<< yytext << '\n'; fposcnt++; }
-{digit}+               { std::cout << "found -ve decimal : " << yytext << '\n'; dnegcnt++; }
-{digit}+\.{digit}*     { std::cout << "found -ve fraction : "<< yytext << '\n'; fnegcnt++; }
{white}                 { ; } // eat whitespaces

