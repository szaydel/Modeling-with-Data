#include <apop.h>

int main(){
    apop_db_open("data-climate.db");
    apop_data *precip = apop_query_to_data("select PCP from precip");
    apop_model *est = apop_estimate(precip, apop_normal);
    Apop_col_tv(precip, "PCP", v);
    apop_plot_qq(v, est, "outfile.gnuplot", .bins=2000);

    double  var     = apop_vector_var(v);
    double  skew    = apop_vector_skew(v)/pow(var, 3/2);
    double  kurt    = apop_vector_kurtosis(v)/gsl_pow_2(var) - 3;
    double  statistic = v->size * (gsl_pow_2(skew)/6. + gsl_pow_2(kurt)/24.);
    printf("The skew is %g, the normalized kurosis is %g, "
            "and we reject the null that your data is Normal with %g confidence.\n", 
        skew, kurt, gsl_cdf_chisq_P(statistic, 2));
}
