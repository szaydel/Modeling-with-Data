#include "eigenbox.h"

int main(){
    apop_data *constr = apop_data_falloc((1, 1, 3), 0, 0, 0, 1);
    apop_data *d = query_data();
    apop_model *est = apop_estimate(d, apop_ols);
    apop_model_show(est);
    apop_data_show(apop_f_test(est, constr));
}
