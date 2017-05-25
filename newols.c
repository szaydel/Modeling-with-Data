#include <apop.h>

apop_model new_OLS;

static void new_ols_estimate(apop_data *d, apop_model *out){
    Apop_col_v(d, 0, v);
    apop_data *ydata = apop_data_alloc(d->matrix->size1, 0, 0);
    gsl_vector_memcpy(ydata->vector, v);
    gsl_vector_set_all(v, 1);     //affine: first column is ones.
    apop_data *xpx = apop_dot(d, d, 't', 0);
    apop_data *inv = &(apop_data){.matrix=apop_matrix_inverse(xpx->matrix)};
    out->data           = d;
    out->parameters     = apop_dot(inv, apop_dot(d, ydata, 1), 0);
}

apop_model new_OLS = {.name ="A simple OLS implementation", 
                        .estimate = new_ols_estimate};

int main(){
    apop_data *dataset = apop_text_to_data("data-regressme", 0, 1);
    apop_model *est = apop_estimate(dataset, &new_OLS);
    apop_model_show(est);
}
