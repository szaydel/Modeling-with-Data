#include <apop.h>
#include "plot_histogram.c"

int     drawct      = 10000;
double  data[]      = {1, 2, 3, 10, 11, 10, 11, 90, 91, 90, 91};

gsl_vector *make_draws(int ct, gsl_rng *r){
    double total;
    gsl_vector *out = gsl_vector_alloc(drawct);
    for(int i=0; i< drawct; i++){
        total = 0;
        for(int j=0; j< ct; j++)
           total += data[gsl_rng_uniform_int(r, sizeof(data)/sizeof(data[0]))];
        gsl_vector_set(out, i, total/ct);
    }
    return out;
}

int main(){
    gsl_rng *r = apop_rng_alloc(23);
    for (int ct=1; ct<= 1018; ct+=3){
        printf("set title 'Mean of %i draws'\n", ct);
        gsl_vector *o =make_draws(ct, r);
        plot_histogram(o, stdout, 200, NULL);
        gsl_vector_free(o);
        printf("pause 0.6\n");
    }
}
