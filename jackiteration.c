#include <apop.h>

typedef double (*math_fn)(apop_data *);

gsl_vector *jack_iteration(gsl_matrix *m, math_fn do_math){
    int height = m->size1;
    gsl_vector *out = gsl_vector_alloc(height);
    apop_data *reduced = apop_data_alloc(0, height - 1, m->size2);
    Apop_submatrix(m, 1, 0, height - 1, m->size2, mv);
    gsl_matrix_memcpy(reduced->matrix, mv);
    for (int i=0; i< height; i++){
        gsl_vector_set(out, i, do_math(reduced));
        if (i < height - 1){
            Apop_matrix_row(m, i, onerow);
            gsl_matrix_set_row(reduced->matrix, i, onerow);
        }
    }
    return out;
}
