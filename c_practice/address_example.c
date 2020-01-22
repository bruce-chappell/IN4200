#include <stdio.h>

int main () {

  int disp[2][4] = {
    {10, 11, 12, 13},
    {14, 15, 16, 17}
  };
  int i;
  int j;
  for(i=0; i<2; i++){
    for(j=0; j<2; j++){
      printf("%p \n", &disp[i][j]);
    }
  }
  return 0;
}
