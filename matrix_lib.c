#include "matrix_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

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
  printf("\n");
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
void preenche_com_zero(s_matrix * matrix){
  for(int i=0; i < matrix->width * matrix->height; i++){
    matrix->rows[i] = 0;
  }
}

int matrix_matrix_mult(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c){
  if(!matrix_a || !matrix_b || !matrix_c){
    return 0;
  }
  int temp;
  for(int i=0; i < matrix_a->height; i++){
    for(int j=0; j < matrix_b->width; j++){
      for(int k=0; k < matrix_a->width; k++){
        temp = matrix_a->rows[get_cell(matrix_a->width, k, i)] * matrix_b->rows[get_cell(matrix_b->width,j ,k)];
        matrix_c->rows[get_cell(matrix_c->width, j, i)] += temp;
      }
    }
  }
  return 1;
}

void write_matrix(s_matrix * matrix, char * name){
  char * n = ("%s.dat", name);
  FILE * f = fopen(n , "w" );
  fwrite(matrix, sizeof(s_matrix), 1, f);
}

s_matrix * read_matrix(char * name){
  FILE * f = fopen(name, "r");
  s_matrix * matrix;
  fread(matrix, sizeof(s_matrix), 1, f);
  return matrix;

}

s_matrix * gen_random_matrix(int width, int height){
  int size = width * height;
  float rows[size];
  for(int i=0; i < size; i++){
    rows[i] = rand() % 10;
  }
  s_matrix * matrix = create_matrix(width, height, rows);

  return matrix;
}