#include <stdio.h>
#include <stdlib.h>
#include "helper_functions.h"

char** matrix_2d (int row, int col){
     char** A = malloc(row * sizeof(char *));
     char* flat_matrix = malloc(row * col* sizeof(char));
     for(size_t i = 0; i < row; i++){
          A[i] = &(flat_matrix[i*col]);
     }
     return A;
}

char** matrix_zeros (int row, int col){
     char** A = matrix_2d(row, col);
     for (int i = 0; i <  row; i++){
          for (int j = 0; j < col; j++){
               A[i][j] = 0;
          }
     }
     return A;
}

int* array_zeros (int len){
     int* A = malloc(len * sizeof(int));
     for (int i = 0; i < len; i++){
          A[i] = 0;
     }
     return A;
}

int* array_neg_one (int len){
     int* A = malloc(len * sizeof(int));
     for (int i = 0; i < len; i++){
          A[i] = -1;
     }
     return A;
}

void printmat (char **A, int n, int m){
     /* Borrowed from Xing */
     for (size_t i = 0; i < n; ++i){
          printf("| ");
          for (size_t j = 0; j < m; ++j){
               printf("%d ", A[i][j]);
          }
          printf("|\n");
     }
}

void printvec (int *A, int len){
     for (int i = 0; i < len; i++){
          printf("%d: %d\n", i, A[i]);
     }
}
