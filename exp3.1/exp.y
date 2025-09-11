%{
	#include <stdio.h>
	#define YYSTYPE double
	#include<stdlib.h>
	int yyerror(char *msg); 
	int yylex(void);
%}

%token DIGIT ID NL
%left '-' '+'
%left '*' '/'
%token '='

%%
stmt : ID '=' exp NL {
	printf("Valid expression\n");
	exit(0);
}
| exp NL {
	printf("Valid expression\n");
	exit(0);
};
exp :exp '+' exp
| exp '-' exp
| exp '*' exp
| exp '/' exp
|'(' exp ')'
| ID
| DIGIT;
%%

int yyerror(char *msg) {
	printf("Invalid string\n");
}

void main () {
	printf("Enter the expression: ");
	yyparse();
}
