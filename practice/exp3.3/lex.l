%{
#include "y.tab.h"
%}

%%

[0-9]+      { yylval = atoi(yytext); return DIGIT; } // Convert number string to integer
[ \t]       ;                                       // Ignore spaces and tabs
\n          { return NL; }                          // End of input
[+\-*/()]   { return yytext[0]; }                   // Operators and parentheses
.           { printf("Invalid character: %s\n", yytext); return 0; }

%%

int yywrap() { return 1; }
