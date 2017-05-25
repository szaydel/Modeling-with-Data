#include <apop.h>
#include "plot_histogram.c"

int main(){
    int		draws	 = 5e6;
    int		bins	 = 100;
    double	mu		 = 0.492;    //also try 3./8.
    double	sigmasq  = 0.093;    //also try 1./24.
    gsl_rng	*r		 = apop_rng_alloc(0);
    gsl_vector *data = gsl_vector_alloc(draws);
    apop_model *m    = apop_beta_from_mean_var(mu, sigmasq);
    for (int i =0; i < draws; i++)
        apop_draw(gsl_vector_ptr(data, i), r, m);
    plot_histogram(data, stdout, bins, "lines");
}
