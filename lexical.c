#include <stdio.h>
#include <string.h>
#include <ctype.h>


int isKeyword(char buffer[]) {
    char *keywords[] = {
        "auto","break","case","char","const","continue","default","do","double",
        "else","enum","extern","float","for","goto","if","int","long","register",
        "return","short","signed","sizeof","static","struct","switch","typedef",
        "union","unsigned","void","volatile","while"
    };
    int n = sizeof(keywords)/sizeof(keywords[0]);

    for (int i = 0; i < n; i++) {
        if (strcmp(keywords[i], buffer) == 0)
            return 1;
    }
    return 0;
}


int isNumber(char buffer[]) {
    int i = 0, dotCount = 0;

    
    if (buffer[0] == '\0')
        return 0;

    
    if (buffer[0] == '+' || buffer[0] == '-')
        i = 1;

    for (; buffer[i] != '\0'; i++) {
        if (buffer[i] == '.') {
            dotCount++;
            if (dotCount > 1)  // more than one dot => not number
                return 0;
        } else if (!isdigit(buffer[i])) {
            return 0;  // non-digit and non-dot char => not number
        }
    }

    return 1;  
}

int main() {
    FILE *fp = fopen("inp.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char ch, next_ch;
    char buffer[100];
    int j = 0;

    char operators[] = "+-*/%=<>";
    char separators[] = "{}();,[]";

    while ((ch = fgetc(fp)) != EOF) {
       
        if (ch == '/') {
            next_ch = fgetc(fp);
            if (next_ch == '/') {
                
                while ((ch = fgetc(fp)) != EOF && ch != '\n');
                if (j > 0) {
                    buffer[j] = '\0';
                    if (isKeyword(buffer))
                        printf("%s is keyword\n", buffer);
                    else if (isNumber(buffer))
                        printf("%s is numeric constant\n", buffer);
                    else
                        printf("%s is an identifier\n", buffer);
                    j = 0;
                }
                continue;
            } else if (next_ch == '*') {
                
                int prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
                if (j > 0) {
                    buffer[j] = '\0';
                    if (isKeyword(buffer))
                        printf("%s is keyword\n", buffer);
                    else if (isNumber(buffer))
                        printf("%s is numeric constant\n", buffer);
                    else
                        printf("%s is an identifier\n", buffer);
                    j = 0;
                }
                continue;
            } else {
                ungetc(next_ch, fp);
                ch = '/';
            }
        }

       
        int isOp = 0;
        for (int k = 0; operators[k] != '\0'; k++) {
            if (ch == operators[k]) {
                if (j > 0) {
                    buffer[j] = '\0';
                    if (isKeyword(buffer))
                        printf("%s is keyword\n", buffer);
                    else if (isNumber(buffer))
                        printf("%s is numeric constant\n", buffer);
                    else
                        printf("%s is an identifier\n", buffer);
                    j = 0;
                }
                printf("%c is operator\n", ch);
                isOp = 1;
                break;
            }
        }
        if (isOp)
            continue;

        
        int isSep = 0;
        for (int k = 0; separators[k] != '\0'; k++) {
            if (ch == separators[k]) {
                if (j > 0) {
                    buffer[j] = '\0';
                    if (isKeyword(buffer))
                        printf("%s is keyword\n", buffer);
                    else if (isNumber(buffer))
                        printf("%s is numeric constant\n", buffer);
                    else
                        printf("%s is an identifier\n", buffer);
                    j = 0;
                }
                printf("%c is separator\n", ch);
                isSep = 1;
                break;
            }
        }
        if (isSep)
            continue;

        
        if (isspace(ch)) {
            if (j > 0) {
                buffer[j] = '\0';
                if (isKeyword(buffer))
                    printf("%s is keyword\n", buffer);
                else if (isNumber(buffer))
                    printf("%s is numeric constant\n", buffer);
                else
                    printf("%s is an identifier\n", buffer);
                j = 0;
            }
            continue;
        }

       
        if (isalnum(ch) || ch == '_' || ch == '.') {
            
            if (ch == '.') {
               
                int dotAlready = 0;
                for (int idx = 0; idx < j; idx++) {
                    if (buffer[idx] == '.') {
                        dotAlready = 1;
                        break;
                    }
                }
                if (dotAlready) {
                    // Dot repeated - treat as token boundary:
                    if (j > 0) {
                        buffer[j] = '\0';
                        if (isKeyword(buffer))
                            printf("%s is keyword\n", buffer);
                        else if (isNumber(buffer))
                            printf("%s is numeric constant\n", buffer);
                        else
                            printf("%s is an identifier\n", buffer);
                        j = 0;
                    }
                    
                    continue;
                } else if (j == 0) {
                    
                    continue;
                }
            }
            buffer[j++] = ch;
        } else {
           
        }
    }

    
    if (j > 0) {
        buffer[j] = '\0';
        if (isKeyword(buffer))
            printf("%s is keyword\n", buffer);
        else if (isNumber(buffer))
            printf("%s is numeric constant\n", buffer);
        else
            printf("%s is an identifier\n", buffer);
    }

    fclose(fp);
    return 0;
}

