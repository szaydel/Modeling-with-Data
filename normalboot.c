#include <apop.h>

int main(){
  int        draws  = 5000, boots = 1000;
  double     mu     = 1., sigma = 3.;
  gsl_rng    *r     = apop_rng_alloc(2);
  gsl_vector *d     = gsl_vector_alloc(draws);
  apop_model *m     = apop_model_set_parameters(apop_normal, mu, sigma);
  apop_data *boot_stats  =  apop_data_alloc(0, boots, 2);
  apop_name_add(boot_stats->names, "mu", 'c');
  apop_name_add(boot_stats->names, "sigma", 'c');
    for (int i =0; i< boots; i++){
        for (int j =0; j< draws; j++)
            apop_draw(gsl_vector_ptr(d, j), r, m); 
        apop_data_set(boot_stats, i, 0, apop_vector_mean(d));
        apop_data_set(boot_stats, i, 1, sqrt(apop_vector_var(d)));
    }
    apop_data_show(apop_data_covariance(boot_stats));
    printf("Actual:\n var(mu) %g\n", gsl_pow_2(sigma)/draws);
    printf("var(sigma): %g\n", gsl_pow_2(sigma)/(2*draws));
}
