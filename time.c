#include <time.h>
#include <apop.h>

int main(){
    gsl_rng *r  = apop_rng_alloc(time(NULL));
    for (int i =0; i< 10; i++)
        printf("%.3g\t", gsl_rng_uniform(r));
    printf("\n");
}
