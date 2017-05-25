#include <apop.h>

apop_model * dummies(int slope_dummies){
    apop_data *d = apop_query_to_mixed_data("mmt", "select riders, year-1977, line "
            "from riders, lines "
            "where riders.station=lines.station "
            "and riders is not null");
    apop_data *dummified = apop_data_to_dummies(d, 0, 't', .append='y');
    if (slope_dummies){
        Apop_col_v(d, 1, yeardata);
        for(int i=0; i < dummified->matrix->size2; i ++){
            Apop_col_v(dummified, i, c);
            gsl_vector_mul(c, yeardata);
        }
    }
    apop_model *out = apop_estimate(dummified, apop_ols);
    apop_model_show(out);
    return out;
}

#ifndef TESTING
int main(){
    apop_db_open("data-metro.db");
    printf("With constant dummies:\n");  dummies(0);
    printf("With slope dummies:\n");     dummies(1);
}
#endif
