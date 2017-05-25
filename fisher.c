#include <apop.h>

double one_chi_sq(apop_data *d, int row, int col, int n){
    Apop_row_v(d, row, vr);
    Apop_col_v(d, col, vc);
    double rowexp = apop_vector_sum(vr)/n;
    double colexp = apop_vector_sum(vc)/n;
    double observed = apop_data_get(d, row, col);
    double expected = n * rowexp * colexp;
    return gsl_pow_2(observed - expected)/expected; 
}

double calc_chi_squared(apop_data *d){
    double total = 0;
    int n = apop_matrix_sum(d->matrix);
    for (int row=0; row <d->matrix->size1; row++)
        for (int col=0; col <d->matrix->size2; col++)
            total += one_chi_sq(d, row, col, n);
    return total;
}

int main(){
    apop_data *data = apop_data_falloc((2, 2),
                           30, 86,
                           24, 38 );
    double stat, chisq;
    stat = calc_chi_squared(data);
    chisq = gsl_cdf_chisq_Q(stat, (data->matrix->size1 - 1)* (data->matrix->size2 - 1));
    printf("chi squared statistic: %g; p, Chi-squared: %g\n", stat,chisq);
    apop_data_show(apop_test_anova_independence(data));
    apop_data_show(apop_test_fisher_exact(data));
}
