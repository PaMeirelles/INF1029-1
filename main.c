#include <stdio.h>
#include <stdlib.h>
#include "matrix_lib.h"
#include <time.h>

int main(int argc, char * argv[]){
  time_t t;
  srand((unsigned) time(&t));
  
  s_matrix * matrix_a = gen_random_matrix(2, 2);
  print_matrix(matrix_a);
  write_matrix(matrix_a, "matrix_a.dat");
  
  
  s_matrix * rm = gen_random_matrix(2, 2);
  read_matrix("matrix_a.dat", rm);
  print_matrix(rm);
  
  return 0;
}