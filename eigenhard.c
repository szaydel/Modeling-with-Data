#include "eigenbox.h"

void find_eigens(gsl_matrix **subject, gsl_vector *eigenvals, gsl_matrix *eigenvecs){
   gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc((*subject)->size1);
   gsl_eigen_symmv(*subject, eigenvals, eigenvecs, w);
   gsl_eigen_symmv_free (w);
   gsl_matrix_free(*subject); *subject  = NULL;
}

gsl_matrix *pull_best_dims(int ds, int dims, gsl_vector *evals, gsl_matrix *evecs){
    size_t indexes[dims], i;
    gsl_matrix *pc_space = gsl_matrix_alloc(ds,dims);

    gsl_sort_vector_largest_index(indexes, dims, evals);
    for (i=0; i<dims; i++){
       Apop_matrix_col(evecs, indexes[i], temp_vector);
       gsl_matrix_set_col(pc_space, i, temp_vector);
    }
    return pc_space;
}

double normalize_v(gsl_vector *v) {apop_vector_normalize(v, NULL, 'm'); return 0;}

int main(){
    int dims = 2;
    apop_data *x = query_data();
    apop_data *cp = apop_data_copy(x);
    int ds = x->matrix->size2;
    gsl_vector *eigenvals   = gsl_vector_alloc(ds);
    gsl_matrix *eigenvecs   = gsl_matrix_alloc(ds, ds);

    apop_map(x, .part='c', .fn_v=normalize_v, .inplace='y');
    apop_data *xpx = apop_dot(x, x, 1, 0);
    find_eigens(&(xpx->matrix), eigenvals, eigenvecs);
    gsl_matrix *pc_space = pull_best_dims(ds, dims, eigenvals, eigenvecs);
    show_projection(pc_space, cp);
}
