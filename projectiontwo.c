#include <apop.h>

gsl_vector *do_OLS(apop_data *set){
    apop_data *d2 = apop_data_copy(set);
    Apop_col_v(d2, 0, firstcol);
    apop_data *y_copy = apop_vector_to_data(apop_vector_copy(firstcol));
    gsl_vector_set_all(firstcol, 1);

    apop_data *xpx = apop_dot(d2, d2, 't');
    apop_data *xpxinv = &(apop_data){.matrix=apop_matrix_inverse(xpx->matrix)}; //$(\Xv'\Xv)^{-1}$
    apop_data *second_part = apop_dot(xpxinv, d2,0,'t');

    apop_data *beta = apop_dot(second_part, y_copy, 0, 0); //$(\Xv'\Xv)^{-1}\Xv'\yv$
    asprintf(&beta->names->title, "The OLS parameters");
    apop_data_show(beta);

    apop_data *projection_matrix = apop_dot(d2, second_part,0,0); //$\Xv(\Xv'\Xv)^{-1}\Xv'$
    return apop_dot(projection_matrix, y_copy, 0,0)->vector;
}
