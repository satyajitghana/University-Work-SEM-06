%{ 
   /* Definition section */
   #include <stdio.h>
   int flag=0; 

   int yylex(void);
   void yyerror(char* s);
%} 
  
%token NUMBER 
  
%left '+' '-'
  
%left '*' '/' '%'
  
%left '(' ')'
  
/* Rule Section */
%% 
  
ArithmeticExpression : E { 
                           printf("\nResult=%d\n", $$); 
                           return 0; 
                        }
                     ; 
 E    :  E'+'E    { printf("E + E\n"); $$ = $1 + $3; } 
      |  E'-'E    { printf("E + E\n"); $$ = $1 - $3; } 
      |  E'*'E    { printf("E * E\n"); $$ = $1 * $3; } 
      |  E'/'E    { printf("E / E\n"); $$ = $1 / $3; } 
      |  E'%'E    { printf("E % E\n"); $$ = $1 % $3; } 
      |  '('E')'  { printf("(E)\n");   $$ = $2; } 
      |  NUMBER   { printf("NUMBER\n");  $$ = $1; } 
      ; 
  
%% 
  