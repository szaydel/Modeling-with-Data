#include <apop.h>
apop_model *econ_101;

static void econ101_estimate(apop_data *choice, apop_model *p){
    Apop_model_add_group(p, apop_mle, .tolerance = 1e-4, .step_size = 1e-2);
    apop_maximum_likelihood(choice, p);
}

static long double budget(apop_data *beta, apop_model* m){
    double price0 = apop_data_get(m->data, 0, 0),
           price1 = apop_data_get(m->data, 1, 0),
           cash = apop_data_get(m->data, 0, -1);
    apop_data *constraint = apop_data_falloc((3, 3, 2),
                  -cash,    -price0,    -price1, 
                  0.,       1.,         0.,     
                  0.,       0.,         1.);   
    return apop_linear_constraint(m->parameters->vector, constraint, 0);
}

static long double econ101_p(apop_data *d, apop_model *m){
    double alpha = apop_data_get(d, 0, 1),
            beta = apop_data_get(d, 1, 1),
            qty0 = apop_data_get(m->parameters, 0, -1),
            qty1 = apop_data_get(m->parameters, 1, -1);
    return pow(qty0, alpha) * pow(qty1, beta);
}    

apop_model *econ_101 = &(apop_model){"Max Cobb-Douglass subject to a budget constraint", 2, 0, 0,
    .estimate = econ101_estimate, .p = econ101_p, .constraint= budget};
