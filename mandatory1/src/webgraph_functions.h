#ifndef WEBGRAPH_FUNCTIONS_H
#define WEBGRAPH_FUNCTIONS_H

void read_graph_from_file1 (char*, int*, char***);
void read_graph_from_file2 (char*, int*, int*, int**, int**);

int count_mutual_links1 (int, char**, int*);
int count_mutual_links1_OMP (int, char**, int*, int);

int count_mutual_links2 (int, int, int*, int*, int*);
int count_mutual_links2_OMP (int, int, int*, int*, int*, int);

void top_n_webpages (int, int*, int);
void top_n_webpages_OMP (int, int*, int, int);

#endif
