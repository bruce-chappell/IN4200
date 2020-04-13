#include <stdio.h>
#include <stdlib.h>

#include "helper_functions.h"
#include "webgraph_functions.h"
//#include "test_functions.h"

void test_read_graph_from_file1(){
     printf("Testing read_graph_from_file1...\n");
     //true values
     int N_true = 8;
     int table2D_true[8][8] = {
          {0, 0, 0, 0, 0, 0, 1, 0},
          {1, 0, 1, 1, 0, 0, 0, 0},
          {1, 0, 0, 0, 0, 0, 0, 0},
          {0, 1, 0, 0, 0, 0, 0, 0},
          {0, 0, 1, 1, 0, 0, 1, 0},
          {0, 0, 0, 1, 1, 0, 0, 1},
          {0, 0, 0, 0, 1, 0, 0, 1},
          {0, 0, 0, 0, 1, 1, 1, 0}
     };

     //function values
     int N;
     char **table2D;
     char *filename;
     filename = "data/test_graph.txt";
     read_graph_from_file1(filename, &N, &table2D);
     //test equality between function values and true values
     int err_count = 0;
     for(int i = 0; i < N; i++){
          for(int j = 0; j < N; j++){
               if(table2D_true[i][j] != table2D[i][j]){
                    err_count += 1;
               }
          }
     }
     if(err_count > 0){
          printf("ERROR: web graph was read improperly\n");
          exit(EXIT_FAILURE);
     }
     else{
          printf("read_graph_from_file1 passed!\n");
     }
}

void test_read_graph_from_file2(){
     printf("Testing read_graph_from_file2...\n");
     //true values
     int N_true = 8, N_links_true = 17;
     int col_idx_true[17] = {6, 0, 2, 3, 0, 1, 2, 3, 6, 3, 4, 7, 4, 7, 4, 5, 6};
     int row_ptr_true[9] = {0, 1, 4, 5, 6, 9, 12, 14, 17};

     //function values
     int N, N_links;
     int *row_ptr;
     int *col_idx;
     char *filename;
     filename = "data/test_graph.txt";
     read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);

     //test equality
     int err_count = 0;
     for(int i = 0; i < N+1; i++){
          if(row_ptr_true[i] != row_ptr[i]){
               err_count += 1;
          }
     }
     for(int j = 0; j < N_links; j++){
          if(col_idx_true[j] != col_idx[j]){
               err_count += 1;
          }
     }
     if(err_count > 0){
          printf("ERROR: web graph was stored improperly to CRS storage\n");
          exit(EXIT_FAILURE);
     }
     else{
          printf("read_graph_from_file2 passed!\n");
     }
}

void test_count_mutual_links1(){
     printf("Testing count_mutual_links1...\n");
     //true values
     int mutual_links_true = 13;
     int num_involvements_true[8] = {2, 0, 4, 6, 5, 2, 4, 3};

     //function values
     int N;
     int mutual_links;
     char **table2D;
     char *filename;
     filename = "data/test_graph.txt";
     read_graph_from_file1(filename, &N, &table2D);
     int *num_involvements = array_zeros(N);
     mutual_links = count_mutual_links1(N, table2D, num_involvements);

     //compare values
     if(mutual_links_true != mutual_links){
          printf("ERROR: wrong total for mutual linkages\n");
          exit(EXIT_FAILURE);
     }
     int err_count = 0;
     for(int i = 0; i < N; i++){
          if(num_involvements_true[i] != num_involvements[i]){
               err_count += 1;
          }
     }
     if(err_count > 0){
          printf("ERROR: num_involvements calculation incorrect\n");
          exit(EXIT_FAILURE);
     }
     else{
          printf("test_count_mutual_links1 passed!\n");
     }

}

void test_count_mutual_links1_OMP(){
     printf("Testing count_mutual_links1_OMP...\n");
     //true values
     int mutual_links_true = 13;
     int num_involvements_true[8] = {2, 0, 4, 6, 5, 2, 4, 3};

     //function values
     int N;
     int mutual_links;
     char **table2D;
     char *filename;
     filename = "data/test_graph.txt";
     read_graph_from_file1(filename, &N, &table2D);
     int *num_involvements = array_zeros(N);
     mutual_links = count_mutual_links1_OMP(N, table2D, num_involvements, 4);

     //compare values
     if(mutual_links_true != mutual_links){
          printf("ERROR: wrong total for mutual linkages\n");
          exit(EXIT_FAILURE);
     }
     int err_count = 0;
     for(int i = 0; i < N; i++){
          if(num_involvements_true[i] != num_involvements[i]){
               err_count += 1;
          }
     }
     if(err_count > 0){
          printf("ERROR: num_involvements calculation incorrect\n");
          exit(EXIT_FAILURE);
     }
     else{
          printf("test_count_mutual_links1_OMP passed!\n");
     }
}

void test_count_mutual_links2(){
     printf("Testing count_mutual_links2...\n");
     //true values
     int mutual_links_true = 13;
     int num_involvements_true[8] = {2, 0, 4, 6, 5, 2, 4, 3};

     //function values
     int N;
     int N_links;
     int mutual_links;
     int *row_ptr;
     int *col_idx;
     char *filename;
     filename = "data/test_graph.txt";
     read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);
     int *num_involvements = array_zeros(N);
     mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);

     //compare values
     if(mutual_links_true != mutual_links){
          printf("ERROR: wrong total for mutual linkages\n");
          exit(EXIT_FAILURE);
     }
     int err_count = 0;
     for(int i = 0; i < N; i++){
          if(num_involvements_true[i] != num_involvements[i]){
               err_count += 1;
          }
     }
     if(err_count > 0){
          printf("ERROR: num_involvements calculation incorrect\n");
          exit(EXIT_FAILURE);
     }
     else{
          printf("test_count_mutual_links2 passed!\n");
     }
}

void test_count_mutual_links2_OMP(){
     printf("Testing count_mutual_links2_OMP...\n");
     //true values
     int mutual_links_true = 13;
     int num_involvements_true[8] = {2, 0, 4, 6, 5, 2, 4, 3};

     //function values
     int N;
     int N_links;
     int mutual_links;
     int *row_ptr;
     int *col_idx;
     char *filename;
     filename = "data/test_graph.txt";
     read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);
     int *num_involvements = array_zeros(N);
     mutual_links = count_mutual_links2_OMP(N, N_links, row_ptr, col_idx, num_involvements, 4);

     //compare values
     if(mutual_links_true != mutual_links){
          printf("ERROR: wrong total for mutual linkages\n");
          exit(EXIT_FAILURE);
     }
     int err_count = 0;
     for(int i = 0; i < N; i++){
          if(num_involvements_true[i] != num_involvements[i]){
               err_count += 1;
          }
     }
     if(err_count > 0){
          printf("ERROR: num_involvements calculation incorrect\n");
          exit(EXIT_FAILURE);
     }
     else{
          printf("test_count_mutual_links2_OMP passed!\n");
     }
}
