#include <stdio.h>

#include "calc.tab.h"

extern int flag;
//driver code
int main() {
    printf("\nEnter Any Arithmetic Expression which  can have operations Addition, Subtraction, Multiplication, Divison, Modulus and Round brackets:\n");

    yyparse();
    if (flag == 0) {
        printf("\nEntered arithmetic expression is Valid\n\n");
    }

    return 0;
}

void yyerror(char* s) {
    printf("\nEntered arithmetic expression is Invalid: %s\n", s);
    flag = 1;
}
