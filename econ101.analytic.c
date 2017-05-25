#include <apop.h>
apop_model *econ_101_analytic;
apop_model *econ_101;

#define fget(r, c) apop_data_get(fixed_params, (r), (c))

static void econ101_analytic_est(apop_data * fixed_params, apop_model *est){
    double budget = fget(0, -1),   p1  = fget(0, 0), p2   = fget(1, 0),
           alpha  = fget(0, 1),   beta = fget(1, 1);
    double x2  = budget/(alpha/beta + 1)/p2,
           x1  = (budget - p2*x2)/p1;
    est->data   = fixed_params;
    est->parameters = apop_data_alloc(2);
    apop_data_fill(est->parameters, x1, x2);
    est->info = apop_data_alloc();
    apop_data_add_named_elmt(est->info, "log likelihood",log(econ_101->p(fixed_params, est)));
}

static void econ101_analytic_score(apop_data *fixed_params, gsl_vector *gradient, apop_model *m){
    double x1 = apop_data_get(m->parameters, 0, -1);
    double x2 = apop_data_get(m->parameters, 1, -1);
    double alpha = fget(0, 1), beta = fget(1, 1);
    gsl_vector_set(gradient, 0, alpha*pow(x1,alpha-1)*pow(x2,beta));
    gsl_vector_set(gradient, 1, beta*pow(x2,beta-1)*pow(x1,alpha));
}

void prep(apop_data *d, apop_model *m){
    apop_score_vtable_add(econ101_analytic_score, econ_101_analytic);
    apop_model_clear(d, m);
}

apop_model *econ_101_analytic = &(apop_model){"Analytically solve Cobb-Douglass maximization subject to a budget constraint", 
    .vsize =2, .estimate=econ101_analytic_est, .prep=prep};
