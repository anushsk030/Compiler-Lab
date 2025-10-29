#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto","break","case","char","const","continue","default","do",
        "double","else","enum","extern","float","for","goto","if",
        "int","long","register","return","short","signed","sizeof",
        "static","struct","switch","typedef","union","unsigned",
        "void","volatile","while"
    };
    int i;
    for (i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char ch, buffer[15], operators[] = "+-*/%=";
    FILE *fp;
    int i, j = 0;
    int in_single_comment = 0, in_multi_comment = 0;

    fp = fopen("inp.txt", "r");
    if (fp == NULL) {
        printf("Error while opening the file\n");
        exit(0);
    }

    while ((ch = fgetc(fp)) != EOF) {
        // Handle single-line comment //
        if (in_single_comment) {
            if (ch == '\n') in_single_comment = 0;
            continue;
        }

        // Handle multi-line comment /* */
        if (in_multi_comment) {
            if (ch == '*' && (ch = fgetc(fp)) == '/')
                in_multi_comment = 0;
            continue;
        }

        // Detect start of comments
        if (ch == '/') {
            char next = fgetc(fp);
            if (next == '/') {        // Single-line comment
                in_single_comment = 1;
                continue;
            } else if (next == '*') { // Multi-line comment
                in_multi_comment = 1;
                continue;
            } else {
                // It's a division operator, not comment
                ungetc(next, fp);
                printf("%c is operator\n", ch);
                continue;
            }
        }

        // Detect operators
        for (i = 0; i < 6; ++i) {
            if (ch == operators[i]) {
                printf("%c is operator\n", ch);
                break;
            }
        }

        // Detect identifiers or keywords
        if (isalnum(ch)) {
            buffer[j++] = ch;
        } else if ((ch == ' ' || ch == '\n' || ch == '\t') && (j != 0)) {
            buffer[j] = '\0';
            j = 0;
            if (isKeyword(buffer))
                printf("%s is keyword\n", buffer);
            else if(isdigit(buffer[0])&&buffer[1]=='\0')
                printf("%s is a number\n", buffer);
                
            else if(isalpha(buffer[0]) || buffer[0] == '_')
                printf("%s is an identifier\n", buffer);
            else
                printf("%s is not a valid identifier\n", buffer);
        }
    }

    fclose(fp);
    return 0;
}



