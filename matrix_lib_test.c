#include "matrix_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include "utility.h"
#include <errno.h>
#include <immintrin.h>

int is_valid(int num){
    if (num%8==0){
        return 1;
    }
    else{
        return 0;
    }
}

void test(char * string_scalar, char * string_width_a, char * string_height_a, char * string_width_b, char * string_height_b, char * arq1, char * arq2, char * arq3, char * arq4, int (f)(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c)){
  float scalar = atof(string_scalar);
  int width_a = atoi(string_width_a);
  int height_a = atoi(string_height_a);
  int width_b = atoi(string_width_b);
  int height_b = atoi(string_height_b);

  if(!(is_valid(width_a) && is_valid(width_b) && is_valid(height_a) && is_valid(height_b))){
    printf("Dimensão não é múltiplo de 8\n");
    exit(1);
  }
  
  struct timeval start, stop;

  FILE * a1 = fopen(arq1, "r");
  FILE * a2 = fopen(arq2, "r");
  FILE * a3 = fopen(arq3, "w");
  FILE * a4 = fopen(arq4, "w");

  s_matrix * matrix_a = aligned_alloc(32, sizeof(s_matrix));
  s_matrix * matrix_b = aligned_alloc(32, sizeof(s_matrix));
  s_matrix * matrix_c = aligned_alloc(32, sizeof(s_matrix));
  
  matrix_a->width = width_a;
  matrix_a->height = height_a;

  matrix_b->width = width_b;
  matrix_b->height = height_b;

  matrix_c->width = width_b;
  matrix_c->height = height_a;
  
  matrix_a->rows = aligned_alloc(32, sizeof(float) * width_a * height_a);
  matrix_b->rows = aligned_alloc(32, sizeof(float) * width_b * height_b);
  matrix_c->rows =aligned_alloc(32, sizeof(float) * width_a * height_b);

  read_matrix(matrix_a, a1);
  read_matrix(matrix_b, a2);

  fill_matrix(matrix_c, 0);

  gettimeofday(&start, NULL);
  scalar_matrix_mult(scalar, matrix_a);
  gettimeofday(&stop, NULL);

  printf("Time for scalar mult: %.2fms\n",   
 timedifference_msec(start, stop));
  write_matrix(matrix_a, a3);

  gettimeofday(&start, NULL);
  f(matrix_a, matrix_b, matrix_c);
  gettimeofday(&stop, NULL);
  printf("Time for matrix mult: %.2fms\n", timedifference_msec(start, stop));


  write_matrix(matrix_c, a4);

  free_matrix(matrix_a);
  free_matrix(matrix_b);
  free_matrix(matrix_c);

  fclose(a1);
  fclose(a2);
  fclose(a3);
  fclose(a4);
}

void comparison(char * string_scalar, char * string_width_a, char * string_height_a, char * string_width_b, char * string_height_b, char * arq1, char * arq2, char * arq3, char * arq4){
  printf("Classic matrix mult: \n");
  test(string_scalar, string_width_a, string_height_a, string_width_b, string_height_b, arq1, arq2, arq3, arq4, old_matrix_matrix_mult);
  printf("Optimized matrix mult: \n");
  test(string_scalar, string_width_a, string_height_a, string_width_b, string_height_b, arq1, arq2, arq3, arq4, op_matrix_matrix_mult);
  printf("Vector matrix mult: \n");
  test(string_scalar, string_width_a, string_height_a, string_width_b, string_height_b, arq1, arq2, arq3, arq4, matrix_matrix_mult);
}

int main(int argc, char * argv[]){
 setup(2048, 2048, 2048, 2048, 8);
 //comparison(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
  test(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], matrix_matrix_mult);
  check_files(2048, 2048, 2048, 2048, 8);
  return 0;
}