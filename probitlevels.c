#include <apop.h>

long double pplc_ll(apop_data *d, apop_model *child_params){
    apop_data *lambdas = apop_dot(d, child_params->parameters);
    apop_data *smallset = apop_data_alloc(1);
    double ll = 0;
    for(size_t i=0; i < d->vector->size; i ++){
        double lambda = apop_data_get(lambdas, i);
        if (lambda < 0) return GSL_NEGINF; //lambda can't be negative; tell optimizer to look elsewhere.
        apop_model *pp = apop_model_set_parameters(apop_poisson, lambda);
        apop_data_set(smallset, .val=apop_data_get(d, i, -1));
        ll += pp->log_likelihood(smallset, pp);
    }
    apop_data_free(smallset);
    return ll;
}

int main(){
    apop_model pplc = {"Poisson parent, linear child", -1, 
                        .log_likelihood= pplc_ll, .prep=apop_probit->prep};
    apop_db_open("data-tattoo.db");
    apop_data *d = apop_query_to_data("select    \
                tattoos.'ct tattoos ever had'+0.0>1 ct, tattoos.'year of birth'  yr,    \
                tattoos.'number of days drank alcohol in last 30 days' booze    \
                from tattoos                        \
                where  yr+0.0 < 97 and ct+0.0 < 10 and booze notnull");
    apop_data *d2 = apop_data_copy(d);
    apop_model_show(apop_estimate(d, &pplc));
    apop_model_show(apop_estimate(d2, apop_ols));
}
