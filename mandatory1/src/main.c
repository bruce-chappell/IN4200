#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "helper_functions.h"
#include "webgraph_functions.h"
#include "test_functions.h"

int main(int argc, char const *argv[]) {

     if(argc != 4){
          printf("------------- ERROR MESSAGE------------------------- \n");
          printf("ERROR1: command line arguement should have the following form\n"
                  "./(final_executable.exe) (parallel/serial) (full_matrix/CRS) (int number of threads)\n\n");
          exit(EXIT_FAILURE);
     }
     char str1[] = "parallel";
     char str2[] = "serial";
     char str3[] = "full_matrix";
     char str4[] = "CRS";
     int p_comp;
     int s_comp;
     int fm_comp;
     int crs_comp;
     int mode;
     //strcmp() returns zero if strings are equal
     p_comp = strcmp(str1, argv[1]);
     s_comp = strcmp(str2, argv[1]);
     fm_comp = strcmp(str3, argv[2]);
     crs_comp = strcmp(str4, argv[2]);

     // pick data file here and how many top pages you want
     char *filename;
     filename = "data/p2p-Gnutella30.txt";
     int top_n = 10;
     int num_threads = atoi(argv[3]);
     int max_thr = omp_get_max_threads();
     if(num_threads > max_thr){
          num_threads = max_thr;
     }

     if(!s_comp && !fm_comp){
          printf("\n\nSERIAL AND FULL MATRIX: 1 THREAD\n\n");
          mode = 1;
     }
     else if(!p_comp && !fm_comp){
          printf("\n\nPARALLEL AND FULL MATRIX: %d THREADS\n\n", num_threads);
          mode = 2;
     }
     else if(!s_comp && !crs_comp){
          printf("\n\nSERIAL AND CRS: 1 THREAD\n\n");
          mode = 3;
     }
     else if(!p_comp && !crs_comp){
          printf("\n\nPARALLEL AND CRS: %d THREADS\n\n", num_threads);
          mode = 4;
     }
     else{
          printf("------------- ERROR MESSAGE------------------------- \n");
          printf("ERROR2: command line arguement should have the following form\n"
                  "./(final_executable.exe) (parallel/serial) (full_matrix/CRS) (int number of threads)\n\n");
          exit(EXIT_FAILURE);
     }

     printf("------------------- UNIT TESTING -----------------\n\n");
     test_read_graph_from_file1();
     test_read_graph_from_file2();
     test_count_mutual_links1();
     test_count_mutual_links1_OMP();
     test_count_mutual_links2();
     test_count_mutual_links2_OMP();

     if(mode == 1){
          int N;
          double start_read, finish_read, time_read;
          double start_count, finish_count, time_count;
          double start_top, finish_top, time_top;
          char **table2D;
          int num_mutual_links;
          //READ
          start_read = omp_get_wtime();
          read_graph_from_file1(filename, &N, &table2D);
          finish_read = omp_get_wtime();
          time_read = finish_read - start_read;
          //COUNT
          int *num_involvements = array_zeros(N);
          start_count = omp_get_wtime();
          num_mutual_links = count_mutual_links1(N, table2D, num_involvements);
          finish_count = omp_get_wtime();
          time_count = finish_count - start_count;
          printf("\n\n------------MUTUAL LINKS BY NODE-----------\n\n");
          printf("total mutual links: %d\n\n", num_mutual_links);
          //TOP WEBPAGES
          printf("\n\n-----------TOP WEB PAGES-------------------\n");
          start_top = omp_get_wtime();
          top_n_webpages(N, num_involvements, top_n);
          finish_top = omp_get_wtime();
          time_top = finish_top - start_top;
          //TIME
          printf("\n\n-----------RUNTIME----------------------\n");
          printf("read_graph_from_file1 time: %f\n", time_read);
          printf("count_mutual_links1 time: %f\n", time_count);
          printf("top_n_webpages time: %f\n\n", time_top);
     }
     else if(mode ==2){
          int N;
          double start_read, finish_read, time_read;
          double start_count, finish_count, time_count;
          double start_top, finish_top, time_top;
          char **table2D;
          int num_mutual_links;
          //READ
          start_read = omp_get_wtime();
          read_graph_from_file1(filename, &N, &table2D);
          finish_read = omp_get_wtime();
          time_read = finish_read - start_read;
          //COUNT
          int *num_involvements = array_zeros(N);
          start_count = omp_get_wtime();
          num_mutual_links = count_mutual_links1_OMP(N, table2D, num_involvements, num_threads);
          finish_count = omp_get_wtime();
          time_count = finish_count - start_count;
          printf("\n\n------------MUTUAL LINKS BY NODE-----------\n\n");
          printf("total mutual links: %d\n\n", num_mutual_links);
          //TOP WEBPAGES
          printf("\n\n-----------TOP WEB PAGES-------------------\n");
          start_top = omp_get_wtime();
          top_n_webpages_OMP(N, num_involvements, top_n, num_threads);
          finish_top = omp_get_wtime();
          time_top = finish_top - start_top;
          //TIME
          printf("\n\n-----------RUNTIME----------------------\n");
          printf("read_graph_from_file1 time: %f\n", time_read);
          printf("count_mutual_links1_OMP time: %f\n", time_count);
          printf("top_n_webpages_OMP time: %f\n\n", time_top);
     }
     else if(mode == 3){
          int N, N_links;
          int *row_ptr, *col_idx;
          double start_read, finish_read, time_read;
          double start_count, finish_count, time_count;
          double start_top, finish_top, time_top;
          int num_mutual_links;
          //READ
          start_read = omp_get_wtime();
          printf("reading file...\n");
          read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);
          finish_read = omp_get_wtime();
          printf("...done reading\n");
          time_read = finish_read - start_read;
          //COUNT
          int *num_involvements = array_zeros(N);
          printf("counting links...\n");
          start_count = omp_get_wtime();
          num_mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
          finish_count = omp_get_wtime();
          time_count = finish_count - start_count;
          printf("\n\n------------MUTUAL LINKS BY NODE-----------\n\n");
          printf("total mutual links: %d\n\n", num_mutual_links);
          //TOP WEBPAGES
          printf("\n\n-----------TOP WEB PAGES-------------------\n");
          start_top = omp_get_wtime();
          top_n_webpages(N, num_involvements, top_n);
          finish_top = omp_get_wtime();
          time_top = finish_top - start_top;
          //TIME
          printf("\n\n-----------RUNTIME----------------------\n");
          printf("read_graph_from_file2 time: %f\n", time_read);
          printf("count_mutual_links2 time: %f\n", time_count);
          printf("top_n_webpages time: %f\n\n", time_top);
     }
     else if(mode == 4){
          int N, N_links;
          int *row_ptr, *col_idx;
          double start_read, finish_read, time_read;
          double start_count, finish_count, time_count;
          double start_top, finish_top, time_top;
          int num_mutual_links;
          //READ
          printf("reading file...\n");
          start_read = omp_get_wtime();
          read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);
          finish_read = omp_get_wtime();
          time_read = finish_read - start_read;
          printf("....done reading\n");
          //COUNT
          int *num_involvements = array_zeros(N);
          printf("counting links...\n");
          start_count = omp_get_wtime();
          num_mutual_links = count_mutual_links2_OMP(N, N_links, row_ptr, col_idx, num_involvements, num_threads);
          finish_count = omp_get_wtime();
          time_count = finish_count - start_count;
          printf("\n\n------------MUTUAL LINKS BY NODE-----------\n\n");
          printf("total mutual links: %d\n\n", num_mutual_links);
          //TOP WEBPAGES
          printf("\n\n-----------TOP WEB PAGES-------------------\n");
          start_top = omp_get_wtime();
          top_n_webpages_OMP(N, num_involvements, top_n, num_threads);
          finish_top = omp_get_wtime();
          time_top = finish_top - start_top;
          //TIME
          printf("\n\n-----------RUNTIME----------------------\n");
          printf("read_graph_from_file2 time: %f\n", time_read);
          printf("count_mutual_links2_OMP time: %f\n", time_count);
          printf("top_n_webpages_OMP time: %f\n\n", time_top);
     }

     return 0;
}
