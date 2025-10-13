#include<stdio.h>
int arr[20][20];
int res[20];
int n;

void findEpsilon(int i){
    res[i] = 1;
    for(int j = 0 ; j < n ; j++){
        if(arr[i][j] == 1){
            findEpsilon(j);
        }
    }
}

void main(){

  printf("Enter the no. of states :");
  scanf("%d",&n);
  FILE *fp = fopen("input.txt","r");
  while(!feof(fp)){
    int state1 , transition , state2;
    fscanf(fp , "%d%d%d",&state1 , &transition , &state2);
    if(transition == 404){
        arr[state1][state2] = 1;
    }
  }

  for(int i = 0 ; i < n ; i++){
    for (int j = 0; j < n; j++) {
        res[j] = 0;  // or any "default" value
    }
    findEpsilon(i);
    printf("E(%d) = {", i);
    for(int j = 0 ; j < n ; j++){
        if(res[j] == 1){
            printf("%d ,",j);
        }
    }
    printf("}\n");
  }
}
