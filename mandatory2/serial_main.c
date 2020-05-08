#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "count_friends_of_ten.c"
#include <time.h>

int main(int argc, char const *argv[]) {
     srand(1);

     if (argc != 2)
     {
          printf("---------------------------- ERROR ----------------------------\n"
                 "ERROR: command line arguement should have the following form\n"
                 "./(final_executable.exe) (preset/custom)\n");
          exit(EXIT_FAILURE);
     }

     char str1[] = "preset";
     char str2[] = "custom";
     //returns 0 if strings are equal
     int mode_preset = strcmp(str1, argv[1]);
     int mode_custom = strcmp(str2, argv[1]);


     if (mode_preset == 0)
     {
          printf("Running friends of 10 program for the following matrix...\n");
          int row = 10;
          int col = 10;
          int **test_mat = malloc(row * sizeof(*test_mat));
          int *flat = malloc(row * col * sizeof(flat));
          for (int i = 0; i < row; i++){
               test_mat[i] = &(flat[i*col]);
          }
          int val_holder[10][10] = {
               {1, 5, 6, 3, 1, 5, 6, 7, 7, 1},
               {2, 4, 4, 1, 7, 3, 5, 1, 4, 8},
               {7, 2, 3, 1, 2, 5, 8, 2, 6, 2},
               {3, 2, 2, 5, 3, 9, 4, 2, 3, 1},
               {1, 2, 5, 4, 3, 6, 7, 8, 5, 3},
               {9, 8, 6, 4, 2, 7, 3, 1, 6, 1},
               {3, 5, 1, 4, 2, 7, 8, 3, 1, 3},
               {8, 5, 2, 5, 2, 6, 2, 7, 2, 5},
               {3, 6, 2, 7, 9, 4, 2, 8, 3, 1},
               {9, 4, 6, 3, 3, 3, 3, 1, 1, 1}
          };
          for (int i = 0; i <  row; i++){
               for (int j = 0; j < col; j++){
                    test_mat[i][j] = val_holder[i][j];
               }
          }
          for (size_t i = 0; i < row; ++i){
               printf("| ");
               for (size_t j = 0; j < col; ++j){
                    printf("%d ", test_mat[i][j]);
               }
               printf("|\n");
          }

          clock_t starttime_1 = clock();
          int answer = count_friends_of_ten(row, col, test_mat);
          double endtime_1 = ((double)(clock() - starttime_1))/CLOCKS_PER_SEC;

          printf("Friends of 10 counted = %d, time = %f\n", answer, endtime_1);

          free(test_mat[0]);
          free(test_mat);
     }

     else if (mode_custom == 0)
     {
          int row;
          int col;
          printf("Enter number of rows, then columns\n");
          scanf("%d%d", &row, &col);
          //allocate memory
          int **test_mat = malloc(row * sizeof(*test_mat));
          int *flat = malloc(row * col * sizeof(flat));
          for (int i = 0; i < row; i++){
               test_mat[i] = &(flat[i*col]);
          }
          //assign values
          for (int i = 0; i <  row; i++){
               for (int j = 0; j < col; j++){
                    test_mat[i][j] = rand() % 10;
               }
          }
          //print mat
          if ((row <= 20) && (col <= 20)){
               printf("Running friends of 10 program for the following matrix...\n");
               for (size_t i = 0; i < row; ++i){
                    printf("| ");
                    for (size_t j = 0; j < col; ++j){
                         printf("%d ", test_mat[i][j]);
                    }
                    printf("|\n");
               }
          }
          clock_t starttime_1 = clock();
          int answer = count_friends_of_ten(row, col, test_mat);
          double endtime_1 = ((double)(clock() - starttime_1))/CLOCKS_PER_SEC;

          printf("Friends of 10 counted = %d, time = %f\n", answer, endtime_1);

          free(test_mat[0]);
          free(test_mat);

     }

     else
     {
          printf("---------------------------- ERROR ----------------------------\n"
                 "ERROR: command line arguement should have the following form\n"
                 "./(final_executable.exe) (preset/custom)\n");
          exit(EXIT_FAILURE);
     }

     return 0;
}
