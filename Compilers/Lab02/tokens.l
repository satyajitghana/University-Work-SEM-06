%{

#include <iostream>

extern int maxlen;
extern std::string maxstring;

%}

%option noyywrap

%%


[a-zA-Z0-9_\+\*\/]+   {
                std::string curr_string(yytext);
                std::cout << "[" << curr_string << " : " << curr_string.length() << "]\n";

                // if the maxstring length is less than the curr_string then store this
                // curr_string
                if ( maxstring.length() <= curr_string.length() ) {
                    maxstring = curr_string;
                }
            }

[ \t\r]     {   }
"\n"        { return 1; }
.           { std::cout << "[UNRECOGNIZED]\n"; }
