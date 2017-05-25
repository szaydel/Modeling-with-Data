#include <apop.h>

void one_df(int df, gsl_rng *r){
  long int i, runct = 1e6;
  gsl_vector 	*v  = gsl_vector_alloc(runct);
    for (i=0; i< runct; i++)
        gsl_vector_set(v, i, gsl_ran_tdist(r, df));
    printf("%i\t %g", df, apop_vector_kurtosis(v)/gsl_pow_2(apop_vector_var(v)));
    if (df > 4)
        printf("\t%g", (3.*df - 6.)/(df-4.));
    printf("\n");
    gsl_vector_free(v);
}

int main(){
  int         df, df_max  = 31;
  gsl_rng     *r  = apop_rng_alloc(0);
    printf("df\t k (est)\t k (actual)\n");
    for (df=1; df< df_max; df++)
        one_df(df, r);
}
