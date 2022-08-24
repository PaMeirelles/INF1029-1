#include <stdio.h>
#include <stdlib.h>
#include "matrix_lib.h"
#include "matrix_lib_test.h"
#include <time.h>


void setup(int width_a, int height_a, int width_b, int height_b, int print){
  FILE * ma = fopen("matrix_a.dat", "w");
  FILE * mb = fopen("matrix_b.dat", "w");
  
  s_matrix * a = malloc(sizeof(s_matrix));
  a = gen_random_matrix(width_a, height_a);
  s_matrix * b = malloc(sizeof(s_matrix)); 
  b = gen_random_matrix(width_b, height_b);

  if(print){
    print_matrix(a);
    print_matrix(b);
  }

  write_matrix(a, ma);
  write_matrix(b, mb);

  fclose(ma);
  fclose(mb);
}

void check_files(int width_a, int height_a, int width_b, int height_b, int print){
  FILE * ma = fopen("matrix_a.dat", "r");
  FILE * mb = fopen("matrix_b.dat", "r");
  FILE * mpr = fopen("pre_result.dat", "r");
  FILE * mr = fopen("result.dat", "r");

  float * rows_a = malloc(sizeof(float) * width_a * height_a);
  float * rows_b = malloc(sizeof(float) * width_b * height_b);
  float * rows_pre_result = malloc(sizeof(float) * width_a * height_a);
  float * rows_result = malloc(sizeof(float) * height_a * width_b);


  s_matrix * a = create_matrix(width_a, height_a, rows_a);
  s_matrix * b = create_matrix(width_b, height_b, rows_b);
  s_matrix * pre_result = create_matrix(width_a, height_a, rows_pre_result);
  s_matrix * result = create_matrix(width_b, height_a, rows_result);

  read_matrix(a, ma);
  read_matrix(b, mb);
  read_matrix(pre_result, mpr);
  read_matrix(result, mr);

  if(print){
  print_matrix(a);
  print_matrix(b);
  print_matrix(pre_result);
  print_matrix(result);
  }

  fclose(ma);
  fclose(mb);
  fclose(mpr);
  fclose(mr);
}

int main(int argc, char * argv[]){
  //setup(2, 2, 2, 2, 1);
 test(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
 check_files(2, 2, 2, 2, 1);

  return 0;
}