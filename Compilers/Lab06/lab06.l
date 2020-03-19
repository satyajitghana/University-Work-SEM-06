%{ 
   /* Definition section */

  #include <iostream>
  #include <string> 
  #define YYSTYPE int
  #include "lab06.tab.h" 
  extern YYSTYPE yylval; 

%} 

%option noyywrap
  
/* Rule Section */
%% 

[0-9]+  { yylval = atoi(yytext); return NUMBER; } 
[ ] ;
[-+\n] return *yytext; 
.                 { return yytext[0]; }
  
%% 
