#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int* copyArray(int n, int* x){
    int * copy = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        copy[i] = x[i];
    }
    return copy;
}

int isPalindrome(char* str){
    char* ptr2 = str + sizeof(str) - 1;
    while(str < ptr2){
        if(*str++ != *ptr2--)
            return 0;
    }
    return 1;
}

void question4(int** a){
    **a = 100;
}

void makeAndPrintMatrix(int n, int m){
    srand(time(NULL));
    int** matrix = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        matrix[i] = (int*)malloc(m * sizeof(int));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j ++){
            matrix[i][j] = rand() % 100;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j ++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i < n; i++){
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    //copyArray
    int arr[5] = {1,2,3,4,5};
    int* copy = copyArray(5, arr);
    
    printf("matrix function\n");
    printf("enter m ");
    int m,n;
    scanf("%d", &m);
    printf("enter n ");
    scanf("%d", &n);
    makeAndPrintMatrix(m,n);
    return 0;

}


//question 7 name is changed and then we do free(name) so you are not acutally freening the allocated memory.