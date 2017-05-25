#include <apop.h>

int main(){
    apop_db_open("data-census.db");
    gsl_vector *n = apop_query_to_vector("select in_per_capita from income "
            "where state= (select state from geography where name ='North Dakota')");
    gsl_vector *s = apop_query_to_vector("select in_per_capita from income  "
            "where state= (select state from geography where name ='South Dakota')");

    double n_count = n->size,
           n_mean  = apop_vector_mean(n),
           n_var   = apop_vector_var(n),
           s_count = s->size,
           s_mean  = apop_vector_mean(s),
           s_var   = apop_vector_var(s);

    double  stat      = fabs(n_mean - s_mean)/ sqrt(n_var/ (n_count-1) + s_var/(s_count-1));
    double confidence = 1 - (2 * gsl_cdf_tdist_Q(stat, n_count + s_count -2));
    printf("Reject the null with %g%% confidence\n", confidence*100);
}
