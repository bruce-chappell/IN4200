#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  int row = 5, column = 3, i, j, count;
  int **matrix = (int **) malloc(row * sizeof(int *)); //reserving ROW number of int pointers
  for (i=0; i<row; i++){
    matrix[i] = (int *) malloc(column * sizeof(int)); //reserving COLUMN number of ints in each ROW pointer
  }
  count = 0;
  for (i=0; i<row; i++){
    for (j=0; j<column; j++){
      matrix[i][j] = count++;
      // printf("mat[%d][%d] = %d \n", i,j,count);
      // printf("address [%d][%d] = %p \n", i, j, &matrix[i][j]);
    }
  }
  // these are the individual arrays that make up the rows.
  // the value they point to is an address
  printf("*(matrix + 0) %p \n", *(matrix + 0));
  printf("*(matrix + 1) %p \n", *(matrix + 1));
  printf("*(matrix + 2) %p \n", *(matrix + 2));
  printf("*(matrix + 3) %p \n", *(matrix + 3));
  printf("*(matrix + 4) %p \n", *(matrix + 4));

  // now we're pointing to the addresses saved in the rows
  printf("-------------------------------------\n");
  printf("*(*(matrix + 0) + 0) %d \n", *(*(matrix + 0) + 0));
  printf("*(matrix +0)[0] %d \n", *(matrix + 0)[0]);


  printf("-------------------------------------\n");
  printf("address with just matrix %p \n", matrix +1);
  printf("address of matrix[0] %p \n", matrix[0] + 1);
  printf("address of matrix[0][0] %p \n", &matrix[0][1]);




  int flip = 0;
  if (flip == 1){
    int *tst, val;
    val = 23;
    tst = &val;
    printf("value %d \n", *tst);
    printf("address pointed to by tst %p \n", tst);
    printf("address of val %p \n", &val);
    printf("address pointed to by tst+1 %p \n", tst+1);
  }


  return 0;
}
