#include "matrix_lib.h"
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
    if((i+1) % matrix->width == 0){
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

void free_matrix(s_matrix * matrix){
  free(matrix->rows);
  free(matrix);
}
int get_cell(int width, int x, int y){
  return width * y + x;
}
void fill_matrix(s_matrix * matrix, int num){
  for(int i=0; i < matrix->width * matrix->height; i++){
    matrix->rows[i] = num;
  }
}
int classic_matrix_matrix_mult(struct matrix* matrixA, struct matrix* matrixB, struct matrix* matrixC) {
    if ((matrixA == NULL) || (matrixB == NULL) || (matrixC == NULL)) {
        printf("one of the matrix struct given is NULL pointer");
        return 0;
    }
    int i, j, k, limit = matrixA->height * matrixB->width;

    for (i = 0; i < matrixA->height; i++) {
        for (j = 0; j < matrixB->width; j++) {
            float sum = 0;
            for (k = 0; k < matrixA->width; k++) {
                sum += matrixA->rows[i * matrixA->width + k] * matrixB->rows[k * matrixB->width + j];
            }
            matrixC->rows[i * matrixC->width + j] = sum;
        }
    }
    return 1;
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

int flawed_matrix_matrix_mult(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c){
  int cell_a, cell_b, cell_c;
  for(int i=0; i<matrix_a->height * matrix_b->height * matrix_b->width; i++){
    cell_a = i / matrix_b->width;
    cell_b = i % (matrix_a->height * matrix_b->height);
    cell_c = (i / (matrix_b->height * matrix_b->width)) * matrix_c->width + i % matrix_c->width;
    matrix_c->rows[cell_c] += matrix_a->rows[cell_a] * matrix_b->rows[cell_b];
}
  return 1;
  }

int trash_matrix_matrix_mult(struct matrix* matrixA, struct matrix* matrixB, struct matrix* matrixC) {
    if ((matrixA == NULL) || (matrixB == NULL) || (matrixC == NULL)) {
        printf("one of the matrix struct given is NULL pointer");
        return 0;
    }
    int i = 0, j, limit = matrixA->height * matrixA->width;
    while (i < limit) {
        for (j = 0; j < limit; j++) {
            matrixC->rows[j] += matrixA->rows[i] * matrixB->rows[j];
            if ((j + 1) % matrixA->height == 0) i++;
        }
    }
    return 1;
} 

void write_matrix(s_matrix * matrix, FILE * f){
  int size = matrix-> width * matrix->height;
  fwrite(matrix->rows, sizeof(float), size, f);
}

void read_matrix(s_matrix * matrix, FILE * f){
  
  int size = matrix-> width * matrix->height;
  
   int s = fread(matrix->rows, sizeof(float), size, f);

  if(s != size){
     printf("Falha na leitura. Apenas %d elementos lidos, %d esperados\n", s, size);
   }
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

int matrix_matrix_mult(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c){
  int counter = 0;
  float * pointer_a = matrix_a->rows;
  float * pointer_b = matrix_b->rows;
  float * pointer_c = matrix_c->rows;
  int wb = matrix_b->width;
  int hb = matrix_b->height;
  int ha = matrix_a->height;
  int size = hb * wb;

 while(counter < ha * wb * hb){
  //rintf("%.0f %.0f %.0f %d   ", *pointer_a, *pointer_b, *pointer_c, counter);
  counter++;

  *pointer_c += *pointer_a * *pointer_b;
  //printf("%.0f %.0f %.0f %d\n", *pointer_a, *pointer_b, *pointer_c, counter);

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
int bernardo_matrix_matrix_mult(struct matrix* matrixA, struct matrix* matrixB, struct matrix* matrixC) {
    if ((matrixA == NULL) || (matrixB == NULL) || (matrixC == NULL)) {
        printf("one of the matrix struct given is NULL pointer");
        return 0;
    }
    int i, j, k, limit = matrixA->height * matrixB->width;

    for (i = 0; i < matrixA->height; i++) {
        for (j = 0; j < matrixB->width; j++) {
            float sum = 0;
            for (k = 0; k < matrixA->width; k++) {
                sum += matrixA->rows[i * matrixA->width + k] * matrixB->rows[k * matrixB->width + j];
            }
            matrixC->rows[i * matrixC->width + j] = sum;
        }
    }
    return 1;
}

// renato_main_opt
int renato_matrix_matrix_mult(struct matrix* matrixA, struct matrix* matrixB, struct matrix* matrixC) {
    if ((matrixA == NULL) || (matrixB == NULL) || (matrixC == NULL)) {
        printf("one of the matrix struct given is NULL pointer");
        return 0;
    }
    int i, j = 0, h = matrixA->height, limit = matrixA->height * matrixA->width;

    for (i = 0; i < limit; i++) {

        for (j = 0; j < limit; j++) {
            matrixC->rows[j] += matrixA->rows[i] * matrixB->rows[j];
            (j + 1) % h ? i : i++;
        }
    }
    return 1;
}