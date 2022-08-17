#include <stdio.h>
#include <stdlib.h>
#include "matrix_lib.h"

int main(){
  float rows[4] = {2, 0, 1, 9};
  float rows_2[4] = {3, 9, 4, 7};
  float rows_3[4] = {1,1,1,1};
  
  s_matrix * a = create_matrix(2, 2, rows);
  s_matrix * b = create_matrix(2, 2, rows_2);
  s_matrix * c = create_matrix(2, 2, rows_3);
  
  preenche_com_zero(c);

  matrix_matrix_mult(a, b, c);
  
  print_matrix(a);
  print_matrix(b);
  print_matrix(c);

  escreve_matriz(a, "matriz_a");
  return 0;
}