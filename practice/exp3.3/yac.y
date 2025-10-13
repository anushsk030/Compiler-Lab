%{
#include <stdio.h>
#include <stdlib.h>
%}

%token DIGIT NL
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

stmt: exp NL       { printf("Result = %d\n", $1); }
    ;

exp: exp '+' exp   { $$ = $1 + $3; }
   | exp '-' exp   { $$ = $1 - $3; }
   | exp '*' exp   { $$ = $1 * $3; }
   | exp '/' exp   { 
       if($3 == 0) {
           printf("Error: Division by zero\n"); exit(1);
       } else {
           $$ = $1 / $3;
       }
   }
   | '(' exp ')'   { $$ = $2; }
   | DIGIT         { $$ = $1; }
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
