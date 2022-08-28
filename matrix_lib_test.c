#include "matrix_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"

void test(char * string_scalar, char * string_width_a, char * string_height_a, char * string_width_b, char * string_height_b, char * arq1, char * arq2, char * arq3, char * arq4){
  float scalar = atof(string_scalar);
  int width_a = atoi(string_width_a);
  int height_a = atoi(string_height_a);
  int width_b = atoi(string_width_b);
  int height_b = atoi(string_height_b);
  
  struct timeval start, stop;

  FILE * a1 = fopen(arq1, "r");
  FILE * a2 = fopen(arq2, "r");
  FILE * a3 = fopen(arq3, "w");
  FILE * a4 = fopen(arq4, "w");

  s_matrix * matrix_a = malloc(sizeof(s_matrix));
  s_matrix * matrix_b = malloc(sizeof(s_matrix));
  s_matrix * matrix_c = malloc(sizeof(s_matrix));
  
  matrix_a->width = width_a;
  matrix_a->height = height_a;

  matrix_b->width = width_b;
  matrix_b->height = height_b;

  matrix_c->width = width_b;
  matrix_c->height = height_a;
  
  matrix_a->rows = malloc(sizeof(float) * width_a * height_a);
  matrix_b->rows = malloc(sizeof(float) * width_b * height_b);
  matrix_c->rows = malloc(sizeof(float) * width_a * height_b);

  read_matrix(matrix_a, a1);
  read_matrix(matrix_b, a2);

  fill_matrix(matrix_c, 0);

  gettimeofday(&start, NULL);
  scalar_matrix_mult(scalar, matrix_a);
  gettimeofday(&stop, NULL);

  printf("Time for scalar mult: %.2fms\n", timedifference_msec(start, stop));
  write_matrix(matrix_a, a3);

  gettimeofday(&start, NULL);
  matrix_matrix_mult(matrix_a, matrix_b, matrix_c);
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