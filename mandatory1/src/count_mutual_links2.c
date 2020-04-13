#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "helper_functions.h"
#include "webgraph_functions.h"

int count_mutual_links2 (int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){
     /*
     This funtion has the same purpose as count_mutual_links1 except it reads the
     mutual links info in CRS form instead of a matrix
     ------------- Inputs-------------
     N: number of web pages
     N_links: number of total web page linkages
     row_ptr: row vector from CRS
     col_idx: column index vector from CRS
     num_involvements: 1-D array filled with zeros of size N
     */

     int involvements;
     int row_tot;
     int row_ahead;
     int row_behind;
     int  mutual_links = 0;

     for (int i = 0; i < N; i++){
          //use row_ptr value and the forward value to calc how many values are in
          //each row
          row_ahead = row_ptr[i+1];
          row_behind = row_ptr[i];
          row_tot = row_ahead - row_behind;
          //number of mutual links each node is involved in is row_tot -1
          if(row_tot > 1){
               involvements = row_tot - 1;
               //add mutual link involvements to each corresponding node
               for (int j = row_behind; j < row_ahead; j++){
                    num_involvements[col_idx[j]] += involvements;
                    mutual_links += involvements;
               }
          }
     }
     mutual_links /= 2;
     return mutual_links;
}

int count_mutual_links2_OMP (int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements, int thr_number){
     /*
     This funtion is the same as count_mutual_links2_OMP except it is parallelized
     with openMP
     ------------- Inputs-------------
     N: number of web pages
     N_links: number of total web page linkages
     row_ptr: row vector from CRS
     col_idx: column index vector from CRS
     num_involvements: 1-D array filled with zeros of size N
     */

     int involvements = 0;
     int row_tot = 0;
     int row_ahead = 0;
     int row_behind = 0;
     int mutual_links = 0;

     #pragma omp parallel for private(row_tot, row_ahead, row_behind, involvements) reduction(+: mutual_links, num_involvements[:N]) num_threads(thr_number)
     for (int i = 0; i < N; i++){
          row_ahead = row_ptr[i+1];
          row_behind = row_ptr[i];
          row_tot = row_ahead - row_behind;
          if (row_tot > 1){
               involvements = row_tot - 1;
               for (int j = row_behind; j < row_ahead; j++){
                    num_involvements[col_idx[j]] += involvements;
                    mutual_links += involvements;
               }
          }

     }
     mutual_links /= 2;
     return mutual_links;
}
