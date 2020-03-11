%{ 
   /* Definition section */

  #include <stdio.h> 
  #include "calc.tab.h" 
  extern int yylval; 

%} 

%option noyywrap
  
/* Rule Section */
%% 
[0-9]+   { 
          yylval=atoi(yytext); 
          return NUMBER; 
         } 
[\t]     ; 
  
[\n]     return 0; 
  
.        return yytext[0]; 
  
%% 
