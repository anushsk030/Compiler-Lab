%{
#include <stdio.h>
int n = 0, k = 0, i = 0, o = 0, num = 0;
%}

%%

(if|else|while|int|switch|for|char)     { printf("%s is a keyword\n", yytext); k++; n++; }

[a-zA-Z_][a-zA-Z0-9_]*                 { printf("%s is an identifier\n", yytext); i++; n++; }

[0-9]+                                 { printf("%s is a number\n", yytext); num++; n++; }

[=+\-*/<>]                             { printf("%s is an operator\n", yytext); o++; n++; }

[ \t]                                  ;  /* Ignore spaces and tabs */

\n                                     { printf("\n--- Lexical Analysis Complete ---\n");
                                         printf("Total tokens: %d\nKeywords: %d\nIdentifiers: %d\nNumbers: %d\nOperators: %d\n",
                                                n, k, i, num, o);
                                         exit(0);
                                       }

.                                      ;  /* Ignore other characters */

%%

int main() {
    printf("Enter the input text:\n");
    yylex();
    return 0;
}

int yywrap() { return 1; }
