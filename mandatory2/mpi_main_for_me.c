#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

#include "MPI_count_friends_of_ten.c"

/*
compiling: mpicc file_name.c
running: $export PMIX_MCA_gds=hash (to suppress that weird error message)
         $mpirun --oversubscribe -np <int_threads> ./file_name.exe

for some reason the default threads it runs with is 4 and yells at you if
want more but dont use --override
*/
int main(int argc, char **argv) {
    /*
     * Code mostly taken from task description
     */
    // Empty values used by rank!=0 to be able to call counting function.
    int M=0, N=0, rank, num_triple_friends, size;
    int **v=NULL;

    srand(time(0));
    int A = rand();
    int B = A % 10;
    printf("A: %d\n", A);
    printf("B: %d\n", B);
    // Initialize multiprocessing
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Rank %i of %i\n", rank, size);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
         printf("Running friends of 10 program for the following matrix...\n");
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
    num_triple_friends = MPI_count_friends_of_ten (M, N, v);
    printf("MPI rank <%d>: number of triple friends=%d\n",rank, num_triple_friends);
    if (rank==0) {
        //deallocation of 2D array
        free(v[0]);
        free(v);
    }
    // Finalize multiprocessing
    MPI_Finalize();
    return 0;
}
