#include "matrix_lib.h"
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include "utility.h"
#include <errno.h>
#include <immintrin.h>

int old_scalar_matrix_mult(float scalar_value, struct matrix *matrix){
  if(matrix == NULL){
    return 1;
  }
  int size = matrix->width * matrix->height;
  for(int i=0; i < size; i++){
    matrix->rows[i] = matrix->rows[i] * scalar_value;
  }
  return 0;
}
int old_matrix_matrix_mult(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c){
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
int op_matrix_matrix_mult(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c){
  long counter = 0;
  float * pointer_a = matrix_a->rows;
  float * pointer_b = matrix_b->rows;
  float * pointer_c = matrix_c->rows;
  long wb = matrix_b->width;
  long hb = matrix_b->height;
  long ha = matrix_a->height;
  long size = hb * wb;

 while(counter < ha * wb * hb){
  counter++;

  *pointer_c += *pointer_a * *pointer_b;

  pointer_c++;
  pointer_b++;
  if(counter % wb == 0){
    pointer_a++;
    pointer_c -= wb;
  }
  if (counter % size == 0){
    pointer_b -= size;
    pointer_c += wb;

  }
 }
    return 1;
}
int matrix_matrix_mult(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c){
  long counter = 0;
  float * pointer_a = matrix_a->rows;
  float * pointer_b = matrix_b->rows;
  float * pointer_c = matrix_c->rows;
  long wb = matrix_b->width;
  long hb = matrix_b->height;
  long ha = matrix_a->height;
  long size = hb * wb;

  __m256 a = _mm256_set1_ps(*pointer_a);
  __m256 b;
  __m256 c;
 while(counter < ha * wb * hb){
  counter += 8;

  b = _mm256_load_ps(pointer_b);
  c = _mm256_load_ps(pointer_c);
  c = _mm256_fmadd_ps(a, b, c);
  _mm256_store_ps(pointer_c, c);
  pointer_c += 8;
  pointer_b += 8;
  if(counter % wb == 0){
    pointer_a++;
    a = _mm256_set1_ps(*pointer_a);
    pointer_c -= wb;
  }
  if (counter % size == 0){
    pointer_b -= size;
    pointer_c += wb;

  }
 }
    return 1;
}
int scalar_matrix_mult(float scalar_value, struct matrix *matrix){
  if(matrix == NULL){
    return 1;
  }
  __m256 a = _mm256_set1_ps(scalar_value);
  __m256 b;
  int size = matrix->width * matrix->height;
  for(int i=0; i < size; i += 8){
    b = _mm256_load_ps(matrix->rows+i);
    b = _mm256_mul_ps(a, b);
    _mm256_store_ps(matrix->rows+i, b);
  }
  return 0;
}