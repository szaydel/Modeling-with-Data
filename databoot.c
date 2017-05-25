#include "oneboot.h"

int main(){
  int       rep_ct  = 10000;
  gsl_rng   *r      = apop_rng_alloc(0);
    apop_db_open("data-census.db");
    gsl_vector *base_data    = apop_query_to_vector("select in_per_capita from income where sumlevel+0.0 =40");
    double      RI           = apop_query_to_float("select in_per_capita from income where sumlevel+0.0 =40 and geo_id2+0.0=44");
    gsl_vector *boot_sample  =  gsl_vector_alloc(base_data->size);
    gsl_vector *replications = gsl_vector_alloc(rep_ct);
    for (int i=0; i< rep_ct; i++){
        one_boot(base_data, r, boot_sample);
        gsl_vector_set(replications, i, apop_mean(boot_sample));
    }
    double stderror = sqrt(apop_var(replications));
    double mean     = apop_mean(replications);
    printf("mean: %g; standard error: %g; (RI-mean)/stderr: %g; p value: %g\n",
       mean, stderror, (RI-mean)/stderror, 2*gsl_cdf_gaussian_Q(fabs(RI-mean), stderror));
}
