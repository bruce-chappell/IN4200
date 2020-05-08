#include <stdio.h>
#include <stdlib.h>

int count_friends_of_ten(int M, int N, int **v){
     // check right rimensions
     if (!(M >= 3 || N >= 3)){
          printf("ERROR: one dimension of the input matrix must be >= 3\n");
          exit(EXIT_FAILURE);
     }
     int count = 0;

     for (int m = 0; m < M; m++)
     {
          for (int n = 0; n < N; n++)
          {
               //vertical bellow value
               if (m < M-2){
                    count += (v[m][n] + v[m+1][n] + v[m+2][n] == 10);
               }
               //diagonal down and to the right
               if (m < M-2 && n < N-2){
                    count += (v[m][n] + v[m+1][n+1] + v[m+2][n+2] == 10);
               }
               //diagonal down and to the left
               if (n > 2 && m < M-2){
                    count += (v[m][n] + v[m+1][n-1] + v[m+2][n-2] == 10);
               }
               //horizontal to the right of value
               if (n < N-2){
                    count += (v[m][n] + v[m][n+1] + v[m][n+2] == 10);
               }
          }
     }

     return count;
}
