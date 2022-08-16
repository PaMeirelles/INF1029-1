#include <stdio.h>
#include <stdlib.h>
#include "matrix_lib.h"

int main(){
  float rows[4] = {1.0, 0.0, 0.0, 1.0};
  s_matrix * a = create_matrix(2, 2, rows);
  print_matrix(a);
  return 0;
}