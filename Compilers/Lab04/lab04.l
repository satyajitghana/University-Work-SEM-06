%{

#include <iostream>

extern int charcnt, wordcnt, spacecnt, eolcnt ;

%}

%option noyywrap

white       [ \n\t]+
digit       [0-9]
integer     [digit]+
exponent    [eE][+-]?{integer}
letter      [a-ZA-Z]
eol         [\n]

%x          WORD

%%

[\n]                { eolcnt++; }
[ \t]               { spacecnt++; }
[a-zA-Z]            { BEGIN(WORD); charcnt++; }
<WORD>[a-zA-Z]      { charcnt++; }
<WORD>[\n]          { BEGIN(INITIAL); wordcnt++; eolcnt++; charcnt++; }
<WORD>[ \t]         { BEGIN(INITIAL); wordcnt++; spacecnt++; charcnt++; }
<WORD>[^a-zA-Z]     { BEGIN(INITIAL); wordcnt++; charcnt++;}
.                   { charcnt++; }
