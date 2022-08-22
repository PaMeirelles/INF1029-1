#include "matrix_lib.h"
#include <stdlib.h>

void test(char * string_scalar, char * string_width_a, char * string_height_a, char * string_width_b, char * string_height_b, char * arq1, char * arq2, char * arq3, char * arq4){

  float scalar = atof(string_scalar);
  int width_a = atoi(string_width_a);
  int height_a = atoi(string_height_a);
  int width_b = atoi(string_width_b);
  int height_b = atoi(string_height_b);
  
  s_matrix * matrix_a = malloc(sizeof(s_matrix));
  s_matrix * matrix_b = malloc(sizeof(s_matrix));
  s_matrix * matrix_c = malloc(sizeof(s_matrix));
  
  matrix_a->width = width_a;
  matrix_a->height = height_a;

  matrix_b->width = width_b;
  matrix_b->height = height_b;

  matrix_c->width = width_a;
  matrix_c->height = width_b;
  
  matrix_a->rows = malloc(sizeof(float) * width_a * height_a);
  matrix_b->rows = malloc(sizeof(float) * width_b * height_b);
  matrix_c->rows = malloc(sizeof(float) * width_a * height_b);
  
  read_matrix(matrix_a, arq1);
  read_matrix(matrix_b, arq2);
  /*
  fill_matrix(matrix_c, 0);

  scalar_matrix_mult(scalar, matrix_a);
  write_matrix(matrix_a, arq3);

  matrix_matrix_mult(matrix_a, matrix_b, matrix_c);
  write_matrix(matrix_c, arq4);
  */
}