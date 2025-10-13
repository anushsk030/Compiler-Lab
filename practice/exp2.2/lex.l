%{
#include <stdio.h>

int lines = 1;
int spaces = 0;
int words = 0;
int characters = 0;
%}

%%

\n              { lines++;  }                     // newline: count line + character
[ \t]+          { spaces += yyleng; characters += yyleng; }   // spaces/tabs: count both
[a-zA-Z0-9_]+   { words++; characters += yyleng; }            // word: count once + add all characters
.                { characters++; }                             // any other single character

%%

int main(void) {
    char fname[100];
    printf("Enter the input file name: ");
    scanf("%s", fname);

    yyin = fopen(fname, "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }
    
    yylex();
    fclose(yyin);

    printf("\n--- File Statistics ---\n");
    if (characters == 0 && spaces == 0  && words == 0){
        lines = 0;
    }
    printf("Lines      : %d\n", lines);
    printf("Words      : %d\n", words);
    printf("Spaces     : %d\n", spaces);
    printf("Characters : %d\n", characters);

    return 0;
}

int yywrap(void) {
    return 1;
}
