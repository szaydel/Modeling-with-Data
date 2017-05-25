#include "eigenbox.h"

long double linear_constraint(apop_data * d, apop_model *m){
    apop_data *constr = apop_data_falloc((1, 1, 3), 0, 0, 0, 1);
    return apop_linear_constraint(m->parameters->vector, constr, 0);
}

void show_chi_squared_test(apop_model *unconstrained, apop_model *constrained, int constraints){
    double statistic = 2 * (apop_data_get(unconstrained->info, .rowname="log likelihood")
                          - apop_data_get(constrained->info, .rowname="log likelihood"));
    double confidence = gsl_cdf_chisq_P(statistic, constraints);
    printf("The Chi squared statistic is: %g, so reject the null of non-binding constraint "
        "with %g%% confidence.\n", statistic, confidence*100);
}

int main(){
   apop_data *d = query_data();
   apop_model *unconstr = apop_estimate(d, apop_ols);
   apop_model_show(unconstr);

   Apop_model_add_group(apop_ols, apop_mle,
                               .starting_pt= unconstr->parameters->vector->data,
                               .step_size= 1e-3);
   apop_ols->estimate = NULL;
   apop_ols->constraint = linear_constraint;
   apop_model *constr = apop_estimate(d, apop_ols);
   printf("New parameters:\n");
   apop_vector_show(constr->parameters->vector);
   show_chi_squared_test(unconstr, constr, 1);
}
