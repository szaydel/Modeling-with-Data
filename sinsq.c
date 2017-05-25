#include <apop.h>

long double sin_square(apop_data *data, apop_model *m){
    double x = apop_data_get(m->parameters, 0, -1);
    return -sin(x)*gsl_pow_2(x);
}

apop_model *sin_sq_model = &(apop_model){"-sin(x) times x^2",1, .p = sin_square};
