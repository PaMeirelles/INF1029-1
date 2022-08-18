#include <stdio.h>
#include <stdlib.h>
#include "matrix_lib.h"
#include <time.h>

int main(int argc, char * argv[]){
  time_t t;
  srand((unsigned) time(&t));
  
  s_matrix * matrix = gen_random_matrix(2, 2);
  read_matrix(matrix, "matrix_b.dat");
  print_matrix(matrix);
  return 0;
}