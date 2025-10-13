%{
#include <stdio.h>
#include <stdlib.h>
%}

%token ID NL

%%

stmt: ID NL     { printf("Valid Identifier\n"); return 0; }
    ;

%%

int main() {
    printf("Enter an identifier: ");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    printf("Invalid Identifier\n");
    return 0;
}
