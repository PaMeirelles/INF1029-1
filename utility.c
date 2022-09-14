#include <stdio.h>
#include <stdlib.h>
#include "matrix_lib.h"
#include <time.h>
#include "utility.h"

#include <errno.h>
#include <immintrin.h>
void setup(int width_a, int height_a, int width_b, int height_b, int print){
  
  FILE * ma = fopen("matrix_a.dat", "w");
  FILE * mb = fopen("matrix_b.dat", "w");
  
  s_matrix * a = aligned_alloc(32, sizeof(s_matrix));
  
  a = gen_random_matrix(width_a, height_a);
  s_matrix * b = aligned_alloc(32, sizeof(s_matrix)); 
  b = gen_random_matrix(width_b, height_b);
  
  if(print){
    print_matrix(a, print);
    print_matrix(b, print);
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

  float * rows_a = aligned_alloc(32, sizeof(float) * width_a * height_a);
  float * rows_b =aligned_alloc(32, sizeof(float) * width_b * height_b);
  float * rows_pre_result =aligned_alloc(32, sizeof(float) * width_a * height_a);
  float * rows_result = aligned_alloc(32, sizeof(float) * height_a * width_b);


  s_matrix * a = create_matrix(width_a, height_a, rows_a);
  s_matrix * b = create_matrix(width_b, height_b, rows_b);
  s_matrix * pre_result = create_matrix(width_a, height_a, rows_pre_result);
  s_matrix * result = create_matrix(width_b, height_a, rows_result);

  read_matrix(a, ma);
  read_matrix(b, mb);
  read_matrix(pre_result, mpr);
  read_matrix(result, mr);

  if(print){
  printf("Matrix a: \n");
  print_matrix(a, print);
  printf("\nMatrix b: \n");
  print_matrix(b, print);
  printf("\nPre result: \n");
  print_matrix(pre_result, print);
  printf("\nResult: \n");
  print_matrix(result, print);
  }

  fclose(ma);
  fclose(mb);
  fclose(mpr);
  fclose(mr);
}
void print_matrix(s_matrix * matrix, int n){

  int size = matrix->width * matrix->height;
  for(int i=0; i < size; i++){
    if(i == n){
      printf(" ... ");
      break;
    }
    printf("%.2f ", matrix->rows[i]);
    if((i+1) % matrix->width == 0){
      printf("\n");
    }
    }

  printf("\n");

}
s_matrix * create_matrix(int width, int height, float * rows){
  s_matrix * matrix = aligned_alloc(32, sizeof(s_matrix));
  matrix->width = width;
  matrix->height = height;
  matrix->rows = aligned_alloc(32, sizeof(float) * width * height);

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
  long size = width * height;
  
  float * rows = aligned_alloc(32, sizeof(float) * size);
  
  for(long i=0; i < size; i++){
    rows[i] = rand() % 10;
  }
  
  s_matrix * matrix = create_matrix(width, height, rows);
  free(rows);
  return matrix;
  
}
