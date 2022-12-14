#include <stdio.h>
struct matrix {
unsigned long int height;
unsigned long int width;
float *rows;
} typedef s_matrix;
int scalar_matrix_mult(float scalar_value, struct matrix *matrix);
void print_matrix(s_matrix * matrix, int elem_num);
s_matrix * create_matrix(int width, int height, float * rows);
int get_cell(int width, int x, int y);
void fill_matrix(s_matrix * matrix, int num);
int matrix_matrix_mult(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c);
void write_matrix(s_matrix * matrix, FILE * f);
void read_matrix(s_matrix * matrix, FILE * f);
s_matrix * gen_random_matrix(int width, int height);
void free_matrix(s_matrix * matrix);
int trash_matrix_matrix_mult(struct matrix* matrixA, struct matrix* matrixB, struct matrix* matrixC);
int classic_matrix_matrix_mult(struct matrix* matrixA, struct matrix* matrixB, struct matrix* matrixC);
int flawed_matrix_matrix_mult(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c);
int bernardo_matrix_matrix_mult(struct matrix* matrixA, struct matrix* matrixB, struct matrix* matrixC);
int renato_matrix_matrix_mult(struct matrix* matrixA, struct matrix* matrixB, struct matrix* matrixC);
int old_matrix_matrix_mult(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c);