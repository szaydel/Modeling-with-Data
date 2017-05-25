#include "eigenbox.h"
gsl_vector *do_OLS(apop_data *set);

gsl_vector *project(apop_data *d, apop_model *m){
    apop_data *d2 = apop_data_copy(d);
    Apop_col_v(d2, 0, ones);
    gsl_vector_set_all(ones, 1);
    return apop_dot(d2, m->parameters, 0, 'v')->vector;
}

int main(){
    apop_data *d = query_data();
    apop_model *m = apop_estimate(d, apop_ols);
    d->vector = project(d, m);
    //d->vector = do_OLS(d);
    d->names->rowct = 0;
    d->names->colct = 0;
    apop_data_print(d, "projected");
    FILE *cmd = fopen("command.gnuplot", "w");
    fprintf(cmd, "set view 20, 90\n\
            splot 'projected' using 1:3:4 with points, 'projected' using 2:3:4\n");
}
