#include <stdio.h>
#include <stdlib.h>
#include "matrix_lib.h"
#include <time.h>

int main(int argc, char * argv[]){
  time_t t;
  srand((unsigned) time(&t));
  s_matrix * matrix_a = gen_random_matrix(2, 2);
  print_matrix(matrix_a);
  return 0;
}