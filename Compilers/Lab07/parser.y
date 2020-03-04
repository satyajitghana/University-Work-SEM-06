%{


%}

%token DIGIT LETTER

%%

start   : LETTER s

s       : LETTER s
        | DIGIT s
        | /* empty */
        ;

%%