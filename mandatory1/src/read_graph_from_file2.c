#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "helper_functions.h"
#include "webgraph_functions.h"

void read_graph_from_file2 (char *filename, int *N, int *N_links, int **row_ptr, int **col_idx){
     /*
     This function does the same thing as read_graph_from_file1 expect saves
     the web linkage information in CRS format instead of a full matrix.

     ------------- Inputs-------------
     filename: name of text file containing mutual links data ex. "links.txt"
     N: address of interger N which will be given the value of the number of nodes
        in the web graph
     N_links: address of integer N_links which will be given the value of the total
              number of linkages in the web graph
     row_ptr: address of a 1-D pointer where the row information will be saved
     col_idx: address of a 1-D pointer where the column indexes will be saved
     */

     //create file object
     FILE *read_here;
     //open text file into created file object
     read_here = fopen(filename, "r");
     //skip first two lines of text file
     fscanf(read_here, "%*[^\n]\n");
     fscanf(read_here, "%*[^\n]\n");
     //read and store number of nodes links at addresses N and N_links
     fscanf(read_here, "%*s %*s %d %*s %d \n", N, N_links);
     //create arrays for CRS storage of zeros and save them at proper addresses
     *col_idx = array_zeros(*N_links);
     *row_ptr = array_zeros(*N + 1);
     //create temporary arrays to store the to and from node data from the text file
     int* to_array = malloc((*N_links) * sizeof(int));
     int* from_array = malloc((*N_links) * sizeof(int));
     int to;
     int from;
     int idx = 0;
     //skip fourth line of text file
     fscanf(read_here, "%*[^\n]\n");
     //store values for to and from arrays and count how many nonzero values are
     //in each row with row_ptr
     while (fscanf(read_here, "%d %d \n", &from, &to) != EOF){
          if(to < *N && from < *N){
               (*row_ptr)[to+1]+=1;
               to_array[idx] = to;
               from_array[idx] = from;
               idx++;
          }
     }
     fclose(read_here);
     //add up row pointer values recursively. now row_ptr has correct form
     for (int i = 1; i < (*N)+1; i++){
          (*row_ptr)[i] += (*row_ptr)[i-1];
     }
     int row_count = 0;
     int col_idx_loc = 0;
     //loop over rows
     for (int i = 0; i < (*N)+1; i++){
          //loop over length of col_idx
          for (int j = 0; j < (*N_links); j++){
               // if the to_array value at j is the same at the row we're on, save
               // the from_array[j] value to col_idk and increase col_idx_loc
               // advancing to the next value in col_idx
               if (to_array[j] == row_count){
                    (*col_idx)[col_idx_loc] = from_array[j];
                    col_idx_loc += 1;
               }
          }
          row_count += 1;
     }

     //print if you want for sanity check
     bool verbose = false;
     if (verbose == true){
          printf("------------- row_ptr ----------------\n");
          printvec((*row_ptr), *N+1);
          printf("------------- col_idx ----------------\n");
          printvec((*col_idx), *N_links);
          printf("------------- TO ----------------\n");
          printvec(to_array, *N_links);
          printf("------------ FROM ---------------\n");
          printvec(from_array, *N_links);
          printf("-------------------------------\n");
     }

     free(to_array);
     free(from_array);
}
