#include <apop.h>
apop_model *econ_101, *econ_101_analytic;

void est_and_score(apop_model *m, apop_data *params){
    gsl_vector *marginals = gsl_vector_alloc(2);
    apop_model *e = apop_estimate(params, m);
    apop_model_show(e);
    printf("\nThe marginal values:\n");
    apop_score(params, marginals, e);
    apop_vector_show(marginals);
    double ll = apop_data_get(e->info, .rowname="log likelihood");
    printf("\nThe maximized utility: %g\n", exp(ll));
}

int main(){
    apop_data *params = apop_data_falloc((2,2,2), 
                            8.4, 1, 0.4, 
                              0, 3, 0.6); //0 is just a dummy.
    sprintf(apop_opts.output_delimiter, "\n");
    est_and_score(econ_101, params);
    est_and_score(econ_101_analytic, params);
}
