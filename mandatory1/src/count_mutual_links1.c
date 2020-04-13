#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include "helper_functions.h"
#include "webgraph_functions.h"

int count_mutual_links1 (int N, char **table2D, int *num_involvements){
     /*
     This program counts the number of times two outgoing links from two different
     web pages go to the same receiving web page. It also writes how many mutual
     involvements each node is involved in in num_involvements
     ------------- Inputs-------------
     N: size of square interaction matrix
     table2D: 2-D matrix of webpage interactions
     num_involvements: 1-D array filled with zeros of size N
     */
     int mutual_links = 0;
     int row_count;
     int involvements;
     bool first;
     //loop over each row
     for (int row = 0; row < N; row++){
          row_count = 0;
          first = true;
          //loop over each element in row
          for (int col = 0; col < N; col++){
               //check if the value is the first non zero element in the row
               if ((table2D[row][col] == 1) && first){
                    //add up non zero occurances in the row
                    for (int z = col; z < N; z++){
                         row_count += table2D[row][z];
                    }
                    //number of mutual links the node in question is involved is
                    //one less than the amount of interactions per row
                    involvements = row_count - 1;
                    first = false;
                    num_involvements[col] += involvements;
                    mutual_links += involvements;
               }
               //add the mutual links involvements to the remaining nodes in the row with
               //non zero values
               else if ((table2D[row][col] == 1) && !first){
                    num_involvements[col] += involvements;
                    mutual_links += involvements;
               }
               else{
                    continue;
               }
          }
     }
     // divide to counteract that we double counted
     mutual_links /= 2;
     return mutual_links;
}

int count_mutual_links1_OMP (int N, char **table2D, int *num_involvements, int thr_number){
     /*
     Same function as count_mutual_links1 but with openMP implementation
     ------------- Inputs-------------
     N: size of square interaction matrix
     table2D: 2-D matrix of webpage interactions
     num_involvements: 1-D array filled with zeros of size N
     */

     int mutual_links = 0;
     int row_count;
     int involvements;
     bool first;

     #pragma omp parallel private(row_count, involvements, first) num_threads(thr_number)
     {
          #pragma omp for reduction(+:mutual_links, num_involvements[:N])
          for (int row = 0; row < N; row++){
               // printf("checking row %d\n", row);
               row_count = 0;
               first = true;
               for (int col = 0; col < N; col++){
                    if ((table2D[row][col] == 1) && first){
                         for (int z = 0; z < N; z++){
                              row_count += table2D[row][z];
                         }
                         involvements = row_count - 1;
                         first = false;
                         num_involvements[col] += involvements;
                         mutual_links += involvements;
                    }
                    else if ((table2D[row][col] == 1) && !first){
                         num_involvements[col] += involvements;
                         mutual_links += involvements;
                    }
                    else{
                         continue;
                    }
               }
          }
     }
     mutual_links /= 2;
     return mutual_links;
}





//
