#include <stdio.h>
#include <stdlib.h>
int main() {

  // METHOD ONE
  int r = 3, c = 4;
  int *arr = (int *)malloc(r * c * sizeof(int));

  int i, j, count = 0;
  for (i = 0; i <  r; i++)
    for (j = 0; j < c; j++)
      *(arr + i*c + j) = ++count;

  for (i = 0; i <  r; i++)
    for (j = 0; j < c; j++)
      printf("%d ", *(arr + i*c + j));


  // METHOD TWO
  int r = 3, c = 4, i, j, count;

  int **arr = (int **)malloc(r * sizeof(int *));
  for (i=0; i<r; i++){
    arr[i] = (int *)malloc(c * sizeof(int));
  }
  // Note that arr[i][j] is same as *(*(arr+i)+j)
  count = 0;
  for (i = 0; i <  r; i++)
    for (j = 0; j < c; j++)
      arr[i][j] = ++count;  // OR *(*(arr+i)+j) = ++count

  for (i = 0; i <  r; i++)
    for (j = 0; j < c; j++)
      printf("%d \n", arr[i][j]);
  printf("%d \n", arr);

  // METHOD THREE
  int r = 3, c = 4, i, j, count;
  int *arr[r];
  for (i=0; i<r; i++)
       arr[i] = (int *)malloc(c * sizeof(int));

  // Note that arr[i][j] is same as *(*(arr+i)+j)
  count = 0;
  for (i = 0; i <  r; i++)
    for (j = 0; j < c; j++)
       arr[i][j] = ++count; // Or *(*(arr+i)+j) = ++count

  for (i = 0; i <  r; i++)
    for (j = 0; j < c; j++)
       printf("%d ", arr[i][j]);


  return 0;
}
