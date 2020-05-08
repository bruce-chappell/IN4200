#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#include "MPI_count_friends_of_ten.c"

int main(int argc, char **argv) {

     /*---------------------- Input error handling ---------------------------------*/
     if (argc != 2)
     {
          printf("\n---------------------------- ERROR ----------------------------\n"
                 "ERROR: command line arguement should have the following form\n"
                 "mpirun -np <int_threads> ./(final_executable.exe) (preset/custom)\n");
          exit(EXIT_FAILURE);
     }
     char str1[] = "preset";
     char str2[] = "custom";
     //returns 0 if strings are equal
     int mode_preset = strcmp(str1, argv[1]);
     int mode_custom = strcmp(str2, argv[1]);

     if(mode_preset == mode_custom)
     {
          printf("---------------------------- ERROR ----------------------------\n"
                 "ERROR: command line arguement should have the following form\n"
                 "mpirun -np <int_threads> ./(final_executable.exe) (preset/custom)\n");
          exit(EXIT_FAILURE);
     }
     /*---------------------------------------------------------------------------------*/

     int numprocs,rank, triple_total;
     int M = 0;
     int N = 0;
     int **v = NULL;

     srand(0);

     MPI_Init(&argc, &argv);
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

     if (rank == 0)
     {
          //use hardcoded matrix
          if (mode_preset == 0)
          {
               printf("Running friends of 10 MPI program for the following matrix...\n");
               M = 10;
               N = 10;
               v = malloc(M * sizeof(*v));
               int *flat = malloc(M * N * sizeof(flat));
               for (int i = 0; i < M; i++)
               {
                    v[i] = &(flat[i*N]);
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
               for (int i = 0; i <  M; i++)
               {
                    for (int j = 0; j < N; j++)
                    {
                         v[i][j] = val_holder[i][j];
                    }
               }
               for (size_t i = 0; i < M; ++i)
               {
                    printf("| ");
                    for (size_t j = 0; j < N; ++j)
                    {
                         printf("%d ", v[i][j]);
                    }
                    printf("|\n");
               }

          }
          //make a custom random matrix where you pick dimensions and it then gets random 0-9 intergers
          if (mode_custom == 0)
          {
               printf("Enter number of rows, then columns, then values in rowwise fashion\n");
               scanf("%d%d", &M, &N);
               //allocate memory
               v = malloc(M * sizeof(*v));
               int *flat = malloc(M * N * sizeof(flat));
               for (int i = 0; i < M; i++){
                    v[i] = &(flat[i*N]);
               }
               //assign values
               for (int i = 0; i <  M; i++){
                    for (int j = 0; j < N; j++){
                         v[i][j] = rand() % 10;
                    }
               }
               //print mat
               if ((M <= 20) && (N <= 20)){
                    printf("Running friends of 10 MPI program for the following matrix...\n");
                    for (size_t i = 0; i < M; ++i){
                         printf("| ");
                         for (size_t j = 0; j < N; ++j){
                              printf("%d ", v[i][j]);
                         }
                         printf("|\n");
                    }
               }
          }
     }
     //all threads count friends
     triple_total = MPI_count_friends_of_ten (M, N, v);
     //release memory from thread 0
     if (rank == 0){
          free(v[0]);
          free(v);
     }
     //make sure all threads are done with reduction call
     MPI_Barrier(MPI_COMM_WORLD);
     if (rank == 0){
          printf("Total friends of 10 found: %d\n", triple_total);
     }
     MPI_Finalize();
     return 0;
}
