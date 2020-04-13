#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "helper_functions.h"
#include "webgraph_functions.h"

void read_graph_from_file1 (char *filename, int *N, char ***table2D){
     /*
     This function reads a text file describing the linkages between web pages
     in a web graph and produces a matrix which represents how the web pages are
     connected

     ------------- Inputs-------------
     filename: name of text file containing mutual links data ex. "links.txt"
     N: address of interger N which will be given the value of the number of nodes
        in the web graph
     table2D: address of a double pointer which will be given the matrix representing
                the web linkages
     */

     //create file object
     FILE *read_here;
     //open text file into created file object
     read_here = fopen(filename, "r");
     //skip first two lines of text file
     fscanf(read_here, "%*[^\n]\n");
     fscanf(read_here, "%*[^\n]\n");
     //read and store number of nodes at address N
     fscanf(read_here, "%*s %*s %d %*s %*d \n", N);
     //store 2D matrix at address
     *table2D = matrix_zeros(*N, *N);
     //skip fourth line
     fscanf(read_here, "%*[^\n]\n");
     int to;
     int from;
     //read values and store them in matrix
     while (fscanf(read_here, "%d %d \n", &from, &to) != EOF){
          if(to < *N && from < *N){
               (*table2D)[to][from] += 1;
          }
     }

     //if you want to print to check that matrix is correct
     bool verbose = false;
     if (verbose == true){
          printmat((*table2D), *N, *N);
     }

     fclose(read_here);
}
