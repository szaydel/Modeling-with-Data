#include "oneboot.h"

void one_boot(gsl_vector *base_data, gsl_rng *r, gsl_vector* boot_sample){
    for (int i =0; i< boot_sample->size; i++)
        gsl_vector_set(boot_sample, i, 
                gsl_vector_get(base_data, gsl_rng_uniform_int(r, base_data->size)));
}
