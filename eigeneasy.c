#include "eigenbox.h"

int main(){
  int dims = 2;
  apop_data *x = query_data();
  apop_data *cp = apop_data_copy(x);
  apop_data *pc_space      = apop_matrix_pca(x->matrix, dims);
    fprintf(stderr, "total explained: %Lf\n", apop_sum(pc_space->vector));
    show_projection(pc_space->matrix, cp);
}
