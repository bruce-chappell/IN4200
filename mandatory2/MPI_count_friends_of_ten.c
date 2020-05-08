#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int MPI_count_friends_of_ten(int M, int N, int **v){

     int rank, numprocs, m_per_thr, remainder, m_plus_ghost, ghost, start, sub_size, total_friends;
     int count = 0;

     MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
     MPI_Comm_rank (MPI_COMM_WORLD, &rank);
     //N is same for all threads
     MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

     if (rank == 0)
     {
          m_per_thr = M / numprocs;
          remainder = M % numprocs;
          start = 0;

          //allocate array for thread 0 to take last chunk of matrix
          //it gets the remaining rows and a ghost row on top
          int m_last_thr = m_per_thr + remainder + 1;
          int** thr_0_array = malloc(m_last_thr * sizeof(int *));
          int* flat_matrix = malloc(m_last_thr * N* sizeof(int));
          for(size_t i = 0; i < m_last_thr; i++){
               thr_0_array[i] = &(flat_matrix[i*N]);
          }

          //store corresponding values for thr_0_array
          for(int m = 0; m < m_last_thr; m++){
               for(int n = 0; n < N; n++){
                    //the extra -1 starts you one row above the block to get ghost pts
                    thr_0_array[m][n] = v[m + m_per_thr*(numprocs - 1) - 1][n];
               }
          }

          //send chunks to other threads
          for (int thr = 1; thr < numprocs; thr ++){

               //add ghost points, 1 row if its the top thread(chunk of mat), 2 if its in the middle somewhere
               if (thr == 1){
                    ghost = 1;
                    m_plus_ghost = m_per_thr + ghost;
               }
               else{
                    ghost = 2;
                    m_plus_ghost = m_per_thr + ghost;
               }

               sub_size = m_plus_ghost * N;
               MPI_Send(&ghost, 1, MPI_INT, thr, 0, MPI_COMM_WORLD);
               MPI_Send(&m_plus_ghost, 1, MPI_INT, thr, 0, MPI_COMM_WORLD);
               MPI_Send(&v[start][0], sub_size, MPI_INT, thr, 0, MPI_COMM_WORLD);
               //makes starting row for next send the corresponding ghost row
               start += m_plus_ghost - 2;
          }

          //COUNT FOR 0 ARRAY
          printf("counting thread 0....\n");
          for (int m = 0; m < m_last_thr; m++){
               for (int n = 0; n < N; n++){
                    //vertical bellow value
                    if (m < m_last_thr-2){
                         count += (thr_0_array[m][n] + thr_0_array[m+1][n] + thr_0_array[m+2][n] == 10);
                    }
                    //diagonal down and to the right
                    if (m < m_last_thr-2 && n < N-2){
                         count += (thr_0_array[m][n] + thr_0_array[m+1][n+1] + thr_0_array[m+2][n+2] == 10);
                    }
                    //diagonal down and to the left
                    if (n > 2 && m < m_last_thr-2){
                         count += (thr_0_array[m][n] + thr_0_array[m+1][n-1] + thr_0_array[m+2][n-2] == 10);
                    }
                    //horizontal to the right of value
                    //excludes ghost row to avoid double counting
                    if (n < N-2 && (m != 0)){
                         count += (thr_0_array[m][n] + thr_0_array[m][n+1] + thr_0_array[m][n+2] == 10);
                    }
               }
          }

          free(thr_0_array[0]);
          free(thr_0_array);
     }

     if (rank != 0)
     {
          MPI_Recv(&ghost, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          MPI_Recv(&m_plus_ghost, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

          //allocate array for thread
          int** thr_array = malloc(m_plus_ghost * sizeof(int *));
          int* flat_matrix = malloc(m_plus_ghost * N* sizeof(int));
          for(size_t i = 0; i < m_plus_ghost; i++){
               thr_array[i] = &(flat_matrix[i*N]);
          }

          MPI_Recv(&(thr_array[0][0]), m_plus_ghost*N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

          //top block of original array, one ghost row bellow we need to ignore for hoizontal
          if(rank == 1){
               printf("counting thread %i....\n", rank);
               for (int m = 0; m < m_plus_ghost; m++){
                    for (int n = 0; n < N; n++){
                         //vertical bellow value
                         if (m < m_plus_ghost-2){
                              count += (thr_array[m][n] + thr_array[m+1][n] + thr_array[m+2][n] == 10);
                         }
                         //diagonal down and to the right
                         if (m < m_plus_ghost-2 && n < N-2){
                              count += (thr_array[m][n] + thr_array[m+1][n+1] + thr_array[m+2][n+2] == 10);
                         }
                         //diagonal down and to the left
                         if (n > 2 && m < m_plus_ghost-2){
                              count += (thr_array[m][n] + thr_array[m+1][n-1] + thr_array[m+2][n-2] == 10);
                         }
                         //horizontal to the right of value
                         //excludes ghost row to avoid double counting
                         if (n < N-2 && (m != m_plus_ghost - 1)){
                              count += (thr_array[m][n] + thr_array[m][n+1] + thr_array[m][n+2] == 10);
                         }
                    }
               }
          }
          //other blocks are middle blocks and have 2 ghost rows
          else{
               printf("counting thread %i....\n", rank);
               for (int m = 0; m < m_plus_ghost; m++){
                    for (int n = 0; n < N; n++){
                         //vertical bellow value
                         if (m < m_plus_ghost-2){
                              count += (thr_array[m][n] + thr_array[m+1][n] + thr_array[m+2][n] == 10);
                         }
                         //diagonal down and to the right
                         if (m < m_plus_ghost-2 && n < N-2){
                              count += (thr_array[m][n] + thr_array[m+1][n+1] + thr_array[m+2][n+2] == 10);
                         }
                         //diagonal down and to the left
                         if (n > 2 && m < m_plus_ghost-2){
                              count += (thr_array[m][n] + thr_array[m+1][n-1] + thr_array[m+2][n-2] == 10);
                         }
                         //horizontal to the right of value
                         //excludes ghost rows to avoid double counting
                         if (n < N-2 && ((m != m_plus_ghost - 1) && (m != 0))){
                              count += (thr_array[m][n] + thr_array[m][n+1] + thr_array[m][n+2] == 10);
                         }
                    }
               }
          }

          free(thr_array[0]);
          free(thr_array);
     }
     MPI_Allreduce(&count, &total_friends, numprocs, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
     return total_friends;
}




//
