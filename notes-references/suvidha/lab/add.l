%{
#include "add.tab.h"
%}

%%
[0-9]+                 {yylval = atoi(yytext); return NUM;}
[+]					{return PLUS;}
[\n]					{return NL;}
.                      {ECHO; yyerror ("unexpected character");}

%%