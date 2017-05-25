#include <apop.h>

apop_model *sin_sq_model;

void do_search(char *name){
    double p[] = {0};
    double result;
    Apop_settings_set(sin_sq_model, apop_mle, starting_pt, p);
    Apop_settings_set(sin_sq_model, apop_mle, method, name);
    apop_model *out  = apop_estimate(NULL, sin_sq_model);
    result = gsl_vector_get(out->parameters->vector, 0);
    printf("The %s algorithm found %g.\n", name, result);
}

int main(){
    apop_opts.verbose ++;
    Apop_model_add_group(sin_sq_model, apop_parts_wanted);
    Apop_model_add_group(sin_sq_model, apop_mle);
    do_search("NM Simplex");
    do_search("FR Cg");
    do_search("Annealing");
    do_search("Newton");
}
