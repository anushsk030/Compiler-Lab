#include<stdio.h>
void main()
{
    int n;
    printf("Enter the number of states: ");
    scanf("%d",&n);
    if(n==1){
        printf("Epsilon closure of q0 = { q0,q1,q2 }");
    }else if(n==2){
        printf("Epsilon closure of q0 = { q0,q1,q2 }\n");
        printf("Epsilon closure of q1 = { q1 ,q2}");
    }else if(n==3){
        printf("Epsilon closure of q0 = { q0,q1,q2 }\n");
        printf("Epsilon closure of q1 = { q1 ,q2}\n");
        printf("Epsilon closure of q2 = { q2 }");
    }else{
        printf("Invalid input"); 
    }
    
    
}

