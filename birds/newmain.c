#include <apop.h>

apop_model flock;

apop_estimate * estimate (apop_data *d, void *p){
    system("rm history.db");
    system("./treeflock");
    apop_db_open("history.db");
    apop_estimate *out = apop_estimate_alloc(d, flock, p);
    out->parameters =apop_query_to_data("select hawks, doves from pop where period = (select max(period) from pop)");
    out->parameters->vector = gsl_vector_alloc(2);
    gsl_vector_set(out->parameters->vector, 0, gsl_matrix_get(out->parameters->matrix, 0, 0));
    gsl_vector_set(out->parameters->vector, 1, gsl_matrix_get(out->parameters->matrix, 0, 1));
    if (out->ep.uses.covariance)
        out->covariance->matrix = apop_jackknife(d, flock, &(out->ep));
    apop_db_close(0);
    return out;
}

apop_model flock = {"arrayflock", 2, estimate};


int main(){
    apop_data *o=apop_data_alloc(1,1);
    o->matrix = gsl_matrix_calloc(100,3);
    apop_estimate_show(flock.estimate(o, NULL));
}
