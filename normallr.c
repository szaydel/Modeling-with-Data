#include <apop.h>

long double linear_constraint(apop_data * d, apop_model *m){
    double limit0 = 2.5,
           limit1 = 0,
           tolerance = 1e-3; // or try GSL_EPSILON_DOUBLE
    double beta0 = apop_data_get(m->parameters, 0, -1),
           beta1 = apop_data_get(m->parameters, 1, -1);
    if (beta0 > limit0 && beta1 > limit1)
        return 0;
    //else create a valid return vector and return a penalty.
    apop_data_set(m->parameters, 0,  -1,GSL_MAX(limit0 + tolerance, beta0)); 
    apop_data_set(m->parameters, 1, -1, GSL_MAX(limit1 + tolerance, beta1));
    return GSL_MAX(limit0 + tolerance - beta0, 0) 
                    + GSL_MAX(limit1 + tolerance - beta1, 0); 
}

int main(){
    apop_model *constrained = apop_model_copy(apop_normal);
    constrained->estimate = NULL;
    constrained->constraint = linear_constraint;
    apop_db_open("data-climate.db"); 
    apop_data *dataset = apop_query_to_data("select pcp from precip");
    apop_model *free = apop_estimate(dataset, apop_normal);
    apop_model *constr = apop_estimate(dataset, constrained);
    apop_model_show(free);
    apop_model_show(constr);
    double test_stat = 2 * (apop_data_get(free->info, .rowname="log likelihood")
                         - apop_data_get(constr->info, .rowname="log likelihood"));
    printf("Reject the null (constraint has no effect) "
           "with %g%% confidence\n",  apop_test(test_stat, "chi", 1) *100);
}
