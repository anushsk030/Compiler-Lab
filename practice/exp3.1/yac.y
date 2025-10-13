%{
#include <stdio.h>
#include <stdlib.h>
%}

%token DIGIT ID NL
%left '+' '-'
%left '*' '/'

%%
stmt: exp NL     { printf("Valid Expression\n"); return 0; }
    ;

exp: exp '+' exp
   | exp '-' exp
   | exp '*' exp
   | exp '/' exp
   | '(' exp ')'
   | DIGIT
   | ID
   ;
%%

int main() {
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    printf("Invalid Expression\n");
    return 0;
}
