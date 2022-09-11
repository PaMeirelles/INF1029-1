#include <stdio.h>
struct matrix {
unsigned long int height;
unsigned long int width;
float *rows;
} typedef s_matrix;
int scalar_matrix_mult(float scalar_value, struct matrix *matrix);
int matrix_matrix_mult(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c);
int old_matrix_matrix_mult(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c);