%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);               // Lexer function declaration
int yyerror(const char *s);    // Error handling function declaration

int valid = 1;
%}

%token digit letter

%%
start : letter s
      ;

s : letter s
  | digit s
  | /* empty */
  ;
%%

int yyerror(const char *s) {
    printf("Its not a identifier!\n");
    valid = 0;
    return 0;
}

int main() {
    printf("Enter a name to tested for identifier : ");
    yyparse();
    if(valid) {
        printf("It is a identifier!\n");
    }
    return 0;
}

