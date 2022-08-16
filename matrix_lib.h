struct matrix {
unsigned long int height;
unsigned long int width;
float *rows;
} typedef s_matrix;
int scalar_matrix_mult(float scalar_value, struct matrix *matrix);
void print_matrix(s_matrix * matrix);
s_matrix * create_matrix(int width, int height, float * rows);
int get_cell(int width, int x, int y);
void preenche_com_zero(s_matrix * matrix);
int matrix_matrix_mult(struct matrix *matrix_a, struct matrix * matrix_b, struct matrix * matrix_c);