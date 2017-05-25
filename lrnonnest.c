#define TESTING
#include "dummies.c"

void show_normal_test(apop_model *unconstrained, apop_model *constrained, int n){
    double statistic = (apop_data_get(unconstrained->info, .rowname="log likelihood")
                      - apop_data_get(constrained->info, .rowname="log likelihood"))/sqrt(n);
    double confidence = gsl_cdf_gaussian_P(fabs(statistic), 1); //one-tailed.
    printf("The Normal statistic is: %g, so reject the null of no difference between models "
        "with %g%% confidence.\n", statistic, confidence*100);
}

int main(){
   apop_db_open("data-metro.db");
   apop_model *m0 = dummies(0);
   apop_model *m1 = dummies(1);
   show_normal_test(m0, m1, m0->data->matrix->size1);
}
