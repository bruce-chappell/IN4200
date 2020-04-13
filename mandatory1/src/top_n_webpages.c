#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "helper_functions.h"
#include "webgraph_functions.h"

void top_n_webpages (int num_webpages, int *num_involvements, int N){
     /*
     Returns the top "N" number of pages in terms of mutual links.
     ------------- Inputs-------------
     num_webpages: the amount pages in the web graph
     num_involvements: array storing the number of mutual involvements each web page
                       participates in
     N: number of N top pages you want returned
     */

     if (N > num_webpages){
          N = num_webpages;
     }
     int *top_vals = array_zeros(N);
     int *top_idx = array_zeros(N);
     //loop over all the webpages involvement counts
     for (int i = 0; i < num_webpages; i++){
          //loop over top_vals
          for (int j = 0; j < N; j++){
               if (num_involvements[i] >= top_vals[j]){
                    //move trailing values down one spot
                    for (int z = N-1; z > j; z--){
                         top_vals[z] = top_vals[z-1];
                         top_idx[z] = top_idx[z-1];
                    }
                    //insert num_involvements values
                    top_vals[j] = num_involvements[i];
                    top_idx[j] = i;
                    break;
               }
          }
     }
     printf("\nTop %d pages: \n\n", N);
     for (int i = 0; i < N; i++){
          printf("page: %d, involvements: %d\n", top_idx[i], top_vals[i]);
     }

     free(top_vals);
     free(top_idx);
}

void top_n_webpages_OMP (int num_webpages, int *num_involvements, int N, int thr_number){
     /*
     Returns the top "N" number of pages in terms of mutual links.
     ------------- Inputs-------------
     num_webpages: the amount pages in the web graph
     num_involvements: array storing the number of mutual involvements each web page
                       participates in
     N: number of N top pages you want returned
     ---------------------------------
     This function uses a different algorithm from top_n_webpages as it was
     easier to parallelize
     */

     if (thr_number > num_webpages){
          thr_number = num_webpages;
     }
     if (N > num_webpages){
          N = num_webpages;
     }
     int block_len = num_webpages / thr_number;
     int *final_idx = array_zeros(N);
     int *top_idx = array_zeros(thr_number * N);

     //fill these arrays with -1 so you catch if a node has zero mutual links
     //else the logic in the loops wont work
     int *final_top = array_neg_one(N);
     int *top_n = array_neg_one(thr_number * N);

     #pragma omp parallel num_threads(thr_number)
     {
          int thr_id = omp_get_thread_num();
          if (thr_id != thr_number - 1){
               int start_i = thr_id * block_len;
               int stop_i = (thr_id + 1) * block_len;
               int start_j = thr_id * N;
               int stop_j = (thr_id + 1) * N;
               //break the num_involvments array into chunks for each thread
               //loop over each value in chunk
               for (int i = start_i; i < stop_i; i++){
                    //check each value in corresponding chuck of "top array"
                    //against value in num_involvements
                    for (int j = start_j; j < stop_j; j++){
                         if (num_involvements[i] >= top_n[j]){
                              //move values one place value down in array
                              for (int z = stop_j-1; z > j; z--){
                                   top_n[z] = top_n[z-1];
                                   top_idx[z] = top_idx[z-1];
                              }
                              //insert value in top spot and keep track of original idx
                              top_n[j] = num_involvements[i];
                              top_idx[j] = i;
                              break;
                         }
                    }
               }
          }
          //for simplicity last thread will get the leftover entries
          else if (thr_id == thr_number - 1){
               int start_i = thr_id * block_len;
               int stop_i = num_webpages;
               int start_j = thr_id * N;
               int stop_j = thr_number * N;
               for (int i = start_i; i < stop_i; i++){
                    //check each value in corresponding chuck of "top array"
                    //against value in num_involvements
                    for (int j = start_j; j < stop_j; j++){
                         if (num_involvements[i] >= top_n[j]){
                              //move values one place value down in array
                              for (int z = stop_j-1; z > j; z--){
                                   top_n[z] = top_n[z-1];
                                   top_idx[z] = top_idx[z-1];
                              }
                              //insert value in top spot and keep track of original idx
                              top_n[j] = num_involvements[i];
                              top_idx[j] = i;
                              break;
                         }
                    }
               }
          }
     }// pragma omp parallel

     //repeat same sort algorithm with the long top_n array and final_top
     int stop_i = thr_number * N;
     for (int i = 0; i < stop_i; i++){
          for (int j = 0; j < N; j++){
               if (top_n[i] >= final_top[j]){
                    for (int z = N-1; z > j; z--){
                         final_top[z] = final_top[z-1];
                         final_idx[z] = final_idx[z-1];
                    }
                    final_top[j] = top_n[i];
                    final_idx[j] = top_idx[i];
                    break;
               }
          }
     }
     printf("\nTop %d pages: \n\n", N);
     for (int i = 0; i < N; i++){
          printf("page: %d, involvements: %d\n", final_idx[i], final_top[i]);
     }
     free(top_idx);
     free(top_n);
     free(final_idx);
     free(final_top);
}//top_n_webpages_OMP
