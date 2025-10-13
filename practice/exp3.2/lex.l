%{
#include "y.tab.h"
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*   {  return ID; }   // Identifier: starts with letter, followed by letters/digits
\n                     { return NL; }   // Newline marks end of input
[ \t]                  ;                // Ignore spaces and tabs
.                      { return yytext[0]; }  // Any other character

%%

int yywrap() { return 1; }
