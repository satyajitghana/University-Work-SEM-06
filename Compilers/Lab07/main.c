#include <stdio.h>
#include <stdlib.h>

#include "parser.tab.h"

int main(int argc, char* argv[]) {
    printf("Enter String : ");
    yyparse();
    printf("valid identifier\n");
    return 0;
}

void yyerror(char* s) {
    printf("invalid: %s\n", s);
    exit(0);
}
