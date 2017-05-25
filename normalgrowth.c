#include <apop.h>
#include "plot_histogram.c"

int     agentct     = 5000;
int     periods     = 50;
int     binct       = 30;
double  pauselength = 0.6;
gsl_rng *r;

void initialize(double *setme){
    *setme = gsl_rng_uniform(r)*100; 
}

void grow(double *val){
    *val *= exp(gsl_ran_gaussian(r,0.1)); 
}

double estimate(gsl_vector *agentlist){
    return apop_vector_mean(agentlist); 
}

int main(){
    gsl_vector *agentlist = gsl_vector_alloc(agentct);
    r = apop_rng_alloc(39);
    apop_vector_apply(agentlist, initialize);
    for (int i=0; i< periods; i++){
        plot_histogram(agentlist, stdout, binct, "lines");
        printf("pause %g\n", pauselength);
        apop_vector_apply(agentlist, grow);
    } 
    fprintf(stderr, "the mean: %g\n", estimate(agentlist));
}
