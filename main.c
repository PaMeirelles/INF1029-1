#include <stdio.h>
#include <stdlib.h>
#include "matrix_lib.h"
#include "matrix_lib_test.h"
#include <time.h>

int main(int argc, char * argv[]){
  // FILE * ma = fopen("matrix_a.dat", "r");
  // FILE * mb = fopen("matrix_b.dat", "r");
  
  // FILE * ma = fopen("matrix_a.dat", "w");
  // FILE * mb = fopen("matrix_b.dat", "w");
  // s_matrix * a = malloc(sizeof(s_matrix));
  // a = gen_random_matrix(16, 8);
  // s_matrix * b = malloc(sizeof(s_matrix)); 
  // b = gen_random_matrix(8, 16);

  // print_matrix(a);
  // print_matrix(b);

  // write_matrix(a, ma);
  // write_matrix(b, mb);
  
  // a->width = 16;
  // a->height = 8;
  
  // a->rows = malloc(sizeof(float) * a->width * a->height);

    
  // b->width = 8;
  // b->height = 16;
  
  // b->rows = malloc(sizeof(float) * b->width * b->height);
  
  // read_matrix(a, ma);
  // read_matrix(b, mb);

  // print_matrix(a);
  // print_matrix(b);
 
  //   printf("here");

  test(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);

  s_matrix * a = malloc(sizeof(s_matrix));
  a->width = 8;
  a->height = 8;
  
  a->rows = malloc(sizeof(float) * a->width * a->height);

  FILE * f = fopen("result.dat", "r");
  read_matrix(a, f);
  print_matrix(a);
  free_matrix(a);
  fclose(f);
  return 0;
}