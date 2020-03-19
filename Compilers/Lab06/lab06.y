%{ 
   /* Definition section */
   #include <stdio.h>
   #include <iostream>
   int flag=0; 

   int yylex(void);
   void yyerror(char* s);

   #define DEBUG
   #undef DEBUG
%} 
  
%token NUMBER 
  
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
  
/* Rule Section */
%% 
  
program : program E '\n' { std::cout << "\b\b:= " << $2 << '\n'; }
        | { }
        ; 
 E    :  E'+'E    {
                    #ifdef DEBUG
                    printf("E + E\n");
                    #endif
                    $$ = $1 + $3; 
                  } 
      |  E'-'E    {
                    #ifdef DEBUG
                    printf("E + E\n");
                    #endif
                    $$ = $1 - $3;
                  } 
      |  E'*'E    { 
                    #ifdef DEBUG 
                    printf("E * E\n"); 
                    #endif 
                    $$ = $1 * $3; 
                  } 
      |  E'/'E    { 
                    #ifdef DEBUG 
                    printf("E / E\n"); 
                    #endif 
                    $$ = $1 / $3; 
                  } 
      |  E'%'E    { 
                    #ifdef DEBUG 
                    printf("E % E\n"); 
                    #endif 
                    $$ = $1 % $3; 
                  } 
      |  '('E')'  { 
                    #ifdef DEBUG 
                    printf("(E)\n");   
                    #endif 
                    $$ = $2; 
                  } 
      |  NUMBER   {
                    #ifdef DEBUG 
                    printf("NUMBER\n");
                    #endif
                    $$ = $1;
                  } 
      ; 
  
%% 
  