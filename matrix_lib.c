#include "matrix_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
int scalar_matrix_mult(float scalar_value, struct matrix *matrix){
  if(matrix == NULL){
    return 1;
  }
  int size = matrix->width * matrix->height;
  for(int i=0; i < size; i++){
    matrix->rows[i] = matrix->rows[i] * scalar_value;
  }
  return 0;
}

void print_matrix(s_matrix * matrix){
  int size = matrix->width * matrix->height;
  for(int i=0; i < size; i++){
    printf("%.2f ", matrix->rows[i]);
    if((i-1) % matrix->height == 0){
      printf("\n");
    }
  }
}

s_matrix * create_matrix(int width, int height, float * rows){
  s_matrix * matrix = malloc(sizeof(s_matrix));
  matrix->width = width;
  matrix->height = height;
  matrix->rows = malloc(sizeof(float) * width * height);

  for(int i=0; i < width * height; i++){
    matrix->rows[i] = rows[i];
  }
  return matrix;
}

int get_cell(int width, int x, int y){
  return width * y + x;
}