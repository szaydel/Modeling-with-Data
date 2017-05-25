#include <apop.h>

typedef double (*math_fn)(apop_data *);
gsl_vector *jack_iteration(gsl_matrix *, math_fn);
apop_data *ols_data;
gsl_vector * predicted;
double p_dot_mse;

double sum_squared_diff(gsl_vector *left, gsl_vector *right){
    gsl_vector_sub(left, right); //destroys the left vector
    return apop_vector_map_sum(left, gsl_pow_2);
}

gsl_vector *project(apop_data *d, apop_model *m){
    return apop_dot(d, m->parameters, 0, 'v')->vector;
}

double cook_math(apop_data *reduced){
    apop_model *r = apop_estimate(reduced, apop_ols);
    double out = sum_squared_diff(project(ols_data, r), predicted)/p_dot_mse;
    apop_model_free(r);
    return out;
}

gsl_vector *cooks_distance(apop_model *in){
    apop_data  *c = apop_data_copy(in->data);
    apop_ols->prep(in->data, in);
    ols_data = in->data;
    predicted = project(in->data, in);
    p_dot_mse  = c->matrix->size2 * sum_squared_diff(in->data->vector, predicted);
    return jack_iteration(c->matrix, cook_math);
}

int main(){
    apop_data  *dataset = apop_text_to_data("data-regressme");
    apop_model *est     = apop_estimate(dataset, apop_ols);
    printf("plot '-'\n");
    strcpy(apop_opts.output_delimiter, "\n");
    apop_vector_show(cooks_distance(est));
}
