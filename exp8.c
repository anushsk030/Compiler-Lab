#include <stdio.h>
#include <string.h>
#include <ctype.h>
char ch = 'A';


void main(){
    char exp[20];
    printf("Enter the expression :");
    scanf("%s", exp);
    
    for(int i = 0 ; i < strlen(exp) ; i++){
        if(exp[i] == '*' || exp[i] == '/'){
            char op1 = exp[i - 1];
            char op2 = exp[i + 1];
            char opr = exp[i];
            printf("\n%c = %c %c %c",ch , op1 , opr , op2);
            exp[i - 1] = ch;
            exp[i + 1] = ch;
            char prev = ch - 1;
            for(int j = 0 ; j < strlen(exp) ; j++){
                if(exp[j] == prev){
                    exp[j] = ch;
                }
            }
            ch++;
        }
    }
    ////////////////////////////////
    for(int i = 0 ; i < strlen(exp) ; i++){
        if(exp[i] == '-' || exp[i] == '+'){
            char op1 = exp[i - 1];
            char op2 = exp[i + 1];
            char opr = exp[i];
            printf("\n%c = %c %c %c",ch , op1 , opr , op2);
            exp[i - 1] = ch;
            exp[i + 1] = ch;
            char prev = ch - 1;
            for(int j = 0 ; j < strlen(exp) ; j++){
                if(exp[j] == prev){
                    exp[j] = ch;
                }
            }
            ch++;
        }
    }
}